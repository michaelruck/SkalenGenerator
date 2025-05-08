#ifndef SKALEN_GENERATOR_H
#define SKALEN_GENERATOR_H

#include <Arduino.h>
#include <stdint.h>

typedef enum {
    IONIAN = 0,         // Dur
    AEOLIAN = 1,        // Natürlich Moll
    DORIAN = 2,         // Jazz-Moll (Dm7)
    PHRYGIAN = 3,       // Spanisch/Flamenco
    LYDIAN = 4,         // Maj7#11
    MIXOLYDIAN = 5,     // Dominant-Skala (Blues-Jazz)
    LOCRIAN = 6,        // m7b5
    MELODIC_MINOR = 7,  // Jazz-Moll
    HARMONIC_MINOR = 8, // Mittelalter/Jazz
    BLUES = 9,          // Blues-Skala
    BEBOP_DOMINANT = 10,// Bebop-Dominant
    BEBOP_MAJOR = 11,   // Bebop-Dur
    PENTATONIC = 12,    // Pentatonik
    WHOLE_TONE = 13,    // Ganztonskala
    ALTERED = 14,       // Super-Locrian
    DIMINISHED = 15,    // Vermindert
    HALF_DIMINISHED = 16,// Halbvermindert
    SCALE_COUNT         // Wichtig für Iteration
} ScaleType;

struct ScaleInfo {
    ScaleType type;
    const char* name;
    const char* description;
};

class SkalenGenerator {
public:
    uint8_t totalNotes;
    uint8_t basePos;

    uint8_t generateScale(uint8_t *scaleArray, uint8_t rootNote, uint8_t scaleTypeNum);
    uint8_t generateScale(uint8_t *scaleArray, uint8_t rootNote, ScaleType scaleType) {
        return generateScale(scaleArray, rootNote, (uint8_t)scaleType);
    }

    // Metadaten-Zugriff
    static const ScaleInfo* getScaleInfo(uint8_t scaleTypeNum);
    static void printAvailableScales(Print& output = Serial);

private:
    const uint8_t* getPattern(uint8_t scaleTypeNum);
    uint8_t getScaleLength(uint8_t scaleTypeNum);
    void sortAscending(uint8_t *array, uint8_t size);
};

#endif
