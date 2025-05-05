#ifndef SKALEN_GENERATOR_H
#define SKALEN_GENERATOR_H

#include <Arduino.h>
#include <stdint.h>

// Enum für alle Skalen (Dur, Moll, Jazz, Modale Skalen)
typedef enum {
    IONIAN,         // Dur
    AEOLIAN,        // Natürlich Moll
    DORIAN,         // Jazz-Moll (Dm7)
    PHRYGIAN,       // Spanisch/Flamenco
    LYDIAN,         // Maj7#11
    MIXOLYDIAN,     // Dominant-Skala (Blues-Jazz)
    LOCRIAN,        // m7b5
    MELODIC_MINOR,  // Jazz-Moll
    HARMONIC_MINOR, // Mittelalter/Jazz
    BLUES,          // Blues-Skala
    BEBOP_DOMINANT, // Bebop-Dominant
    BEBOP_MAJOR,    // Bebop-Dur
    PENTATONIC,     // Pentatonik
    WHOLE_TONE,     // Ganztonskala
    ALTERED,        // Super-Locrian
    DIMINISHED,     // Vermindert
    HALF_DIMINISHED // Halbvermindert
} ScaleType;

class SkalenGenerator {
public:
    void generateScale(uint8_t *scaleArray, uint8_t rootNote, ScaleType scaleType, uint8_t &totalNotes);
    uint8_t getScaleLength(ScaleType scaleType);

private:
    const uint8_t* getPattern(ScaleType scaleType);
};

#endif
