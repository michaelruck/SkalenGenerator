#include "SkalenGenerator.h"

const ScaleInfo SCALE_DB[] = {
    {IONIAN, "Dur (Ionisch)", "C D E F G A B"},
    {AEOLIAN, "Natürlich Moll (Äolisch)", "A B C D E F G"},
    {DORIAN, "Dorian (Jazz-Moll)", "D E F G A B C"},
    {PHRYGIAN, "Phrygisch", "E F G A B C D"},
    {LYDIAN, "Lydisch", "F G A B C D E"},
    {MIXOLYDIAN, "Mixolydisch", "G A B C D E F"},
    {LOCRIAN, "Lokrisch", "B C D E F G A"},
    {MELODIC_MINOR, "Melodisch Moll", "A B C D E F# G#"},
    {HARMONIC_MINOR, "Harmonisch Moll", "A B C D E F G#"},
    {BLUES, "Blues-Skala", "C Eb F F# G Bb"},
    {BEBOP_DOMINANT, "Bebop Dominant", "C D E F G A Bb B"},
    {BEBOP_MAJOR, "Bebop Dur", "C D E F G A Bb B"},
    {PENTATONIC, "Pentatonik", "C D E G A"},
    {WHOLE_TONE, "Ganztonskala", "C D E F# G# A#"},
    {ALTERED, "Altered Scale", "C Db Eb E Gb Ab Bb"},
    {DIMINISHED, "Verminderte", "C D Eb F Gb Ab A B"},
    {HALF_DIMINISHED, "Halbvermindert", "C D Eb F G Ab Bb"}
};

const uint8_t patterns[][12] = {
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

void SkalenGenerator::printAvailableScales(Print& output) {
    //output.println("Verfügbare Skalen:");
    for (uint8_t i = 0; i < SCALE_COUNT; i++) {
        output.printf("%2d: %-18s - %s\n", i, SCALE_DB[i].name, SCALE_DB[i].description);
    }
}

const ScaleInfo* SkalenGenerator::getScaleInfo(uint8_t scaleTypeNum) {
    if (scaleTypeNum >= SCALE_COUNT) return nullptr;
    return &SCALE_DB[scaleTypeNum];
}

uint8_t SkalenGenerator::generateScale(uint8_t *scaleArray, uint8_t rootNote, uint8_t scaleTypeNum) {
    totalNotes = 0;
    basePos = 255;

    if (scaleTypeNum >= SCALE_COUNT) return 255;

    const uint8_t *pattern = getPattern(scaleTypeNum);
    uint8_t length = getScaleLength(scaleTypeNum);

    // Abwärts bis MIDI 0
    int16_t currentNote = rootNote;
    while (currentNote >= 0) {
        scaleArray[totalNotes] = currentNote;
        if (currentNote == rootNote) basePos = totalNotes;
        totalNotes++;
        uint8_t step = pattern[(length - (rootNote - currentNote) % length) % length];
        currentNote -= step;
    }

    // Aufwärts bis MIDI 127
    currentNote = rootNote + pattern[0];
    while (currentNote <= 127 && totalNotes < 128) {
        scaleArray[totalNotes] = currentNote;
        if (currentNote == rootNote && basePos == 255) basePos = totalNotes;
        totalNotes++;
        uint8_t step = pattern[(currentNote - rootNote) % length];
        currentNote += step;
    }

    sortAscending(scaleArray, totalNotes);
    for (uint8_t i = 0; i < totalNotes; i++) {
        if (scaleArray[i] == rootNote) {
            basePos = i;
            break;
        }
    }

    return basePos;
}

void SkalenGenerator::sortAscending(uint8_t *array, uint8_t size) {
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

uint8_t SkalenGenerator::getScaleLength(uint8_t scaleTypeNum) {
    switch (scaleTypeNum) {
        case BLUES: return 6;
        case BEBOP_DOMINANT:
        case BEBOP_MAJOR:
        case DIMINISHED: return 8;
        case PENTATONIC: return 5;
        case WHOLE_TONE: return 6;
        default: return 7;
    }
}

const uint8_t* SkalenGenerator::getPattern(uint8_t scaleTypeNum) {
    if (scaleTypeNum >= SCALE_COUNT) return patterns[IONIAN];
    return patterns[scaleTypeNum];
}
