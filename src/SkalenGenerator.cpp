#include "SkalenGenerator.h"

const uint8_t PROGMEM patterns[][12] = {
    {2, 2, 1, 2, 2, 2, 1},                   // IONIAN
    {2, 1, 2, 2, 1, 2, 2},                    // AEOLIAN
    {2, 1, 2, 2, 2, 1, 2},                    // DORIAN
    {1, 2, 2, 2, 1, 2, 2},                    // PHRYGIAN
    {2, 2, 2, 1, 2, 2, 1},                    // LYDIAN
    {2, 2, 1, 2, 2, 1, 2},                    // MIXOLYDIAN
    {1, 2, 2, 1, 2, 2, 2},                    // LOCRIAN
    {2, 1, 2, 2, 2, 2, 1},                    // MELODIC_MINOR
    {2, 1, 2, 2, 1, 3, 1},                    // HARMONIC_MINOR
    {3, 2, 1, 1, 3, 2},                       // BLUES
    {2, 2, 1, 2, 2, 1, 1, 1},                 // BEBOP_DOMINANT
    {2, 2, 1, 2, 1, 1, 2, 1},                 // BEBOP_MAJOR
    {3, 2, 2, 3, 2},                          // PENTATONIC
    {2, 2, 2, 2, 2, 2},                       // WHOLE_TONE
    {1, 2, 1, 2, 2, 2, 2},                    // ALTERED
    {2, 1, 2, 1, 2, 1, 2, 1},                 // DIMINISHED
    {1, 2, 1, 2, 1, 3, 1}                     // HALF_DIMINISHED
};

// Hilfsfunktion: Sortiert das Array aufsteigend
void sortAscending(uint8_t *array, uint8_t size) {
    for (uint8_t i = 0; i < size - 1; i++) {
        for (uint8_t j = i + 1; j < size; j++) {
            if (array[i] > array[j]) {
                uint8_t temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void SkalenGenerator::generateScale(uint8_t *scaleArray, uint8_t rootNote, ScaleType scaleType, uint8_t &totalNotes) {
    const uint8_t *pattern = getPattern(scaleType);
    uint8_t length = getScaleLength(scaleType);
    totalNotes = 0;

    // Abwärts bis MIDI 0
    int16_t currentNote = rootNote;
    while (currentNote >= 0) {
        scaleArray[totalNotes++] = currentNote;
        uint8_t step = pattern[(length - (rootNote - currentNote) % length) % length];
        currentNote -= step;
    }

    // Aufwärts bis MIDI 127 (beginnend nach der Basisnote)
    currentNote = rootNote + pattern[0];
    while (currentNote <= 127) {
        if (totalNotes >= 128) break;
        scaleArray[totalNotes++] = currentNote;
        uint8_t step = pattern[(currentNote - rootNote) % length];
        currentNote += step;
    }
    // 2. Sortiere das Ergebnis aufsteigend
    sortAscending(scaleArray, totalNotes);

}

uint8_t SkalenGenerator::getScaleLength(ScaleType scaleType) {
    switch (scaleType) {
        case BLUES: return 6;
        case BEBOP_DOMINANT:
        case BEBOP_MAJOR:
        case DIMINISHED: return 8;
        case PENTATONIC: return 5;
        case WHOLE_TONE: return 6;
        default: return 7;
    }
}

const uint8_t* SkalenGenerator::getPattern(ScaleType scaleType) {
    return patterns[scaleType];
}
