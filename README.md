# SkalenGenerator

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub](https://img.shields.io/badge/GitHub-michaelruck-blue)](https://github.com/michaelruck)

Arduino library for complete MIDI scale generation by [Michael Ruck](mailto:michael.ruck@marsgasse.com).

## Complete Scale Reference

| ID | Constant          | Intervals        | Example Notes (C) | Typical Chords |
|----|-------------------|------------------|-------------------|----------------|
| 0  | `IONIAN`          | W-W-H-W-W-W-H    | C D E F G A B     | Cmaj7, G6      |
| 1  | `AEOLIAN`         | W-H-W-W-H-W-W    | A B C D E F G     | Am7, Dm9       |
| 2  | `DORIAN`          | W-H-W-W-W-H-W    | D E F G A B C     | Dm7, Gm11      |
| 3  | `PHRYGIAN`        | H-W-W-W-H-W-W    | E F G A B C D     | E7♭9, Fm       |
| 4  | `LYDIAN`          | W-W-W-H-W-W-H    | F G A B C D E     | Fmaj7#11       |
| 5  | `MIXOLYDIAN`      | W-W-H-W-W-H-W    | G A B C D E F     | G7, C9         |
| 6  | `LOCRIAN`         | H-W-W-H-W-W-W    | B C D E F G A     | Bm7♭5         |
| 7  | `MELODIC_MINOR`   | W-H-W-W-W-W-H    | A B C D E F# G#   | Am6, B7alt     |
| 8  | `HARMONIC_MINOR`  | W-H-W-W-H-WH-H   | A B C D E F G#    | AmMaj7, E7     |
| 9  | `BLUES`           | 3-2-1-1-3-2      | C Eb F F# G Bb    | C7, F7         |
| 10 | `BEBOP_DOMINANT`  | W-W-H-W-W-H-H-H  | C D E F G A Bb B  | C7, G9         |
| 11 | `BEBOP_MAJOR`     | W-W-H-W-H-H-W-H  | C D E F G Ab Bb B | C6, Fmaj7      |
| 12 | `PENTATONIC`      | W-W-3-W-3        | C D E G A         | Csus2, Am      |
| 13 | `WHOLE_TONE`      | W-W-W-W-W-W      | C D E F# G# A#    | C7#5, D7♭5     |
| 14 | `ALTERED`         | H-W-H-W-W-W-W    | C Db Eb E Gb Ab Bb| C7alt, G#7#9   |
| 15 | `DIMINISHED`      | W-H-W-H-W-H-W-H  | C D Eb F Gb Ab A B| C°7, D7♭9      |
| 16 | `HALF_DIMINISHED` | H-W-H-W-H-3-H    | C Db Eb F Gb Ab Bb| Cm7♭5, F#7alt  |

## Full API

### Scale Generation
```cpp
/**
 * @param notes     Output buffer (uint8_t[128])
 * @param root      MIDI root note (0-127)
 * @param type      Scale type (0-16)
 * @return          Position of root note in array
 */
uint8_t generateScale(uint8_t* notes, uint8_t root, uint8_t type);
```

### Metadata Access
```cpp
// Get all available scales
static const ScaleInfo* getAllScales(uint8_t* count);

struct ScaleInfo {
    uint8_t id;
    const char* name;
    const char* intervals;
    const char* chords;
};
```

### LVGL Utilities
```cpp
// Create pre-configured dropdown
static lv_obj_t* createLVGLDropdown(lv_obj_t* parent);
```

## Example Output
```
=== C Ionian ===
Notes (72): 
 0(12)  2  4  5  7  9 11 
12(24) 14 16 17 19 21 23 
... 
(60)62 64 65 67 69 71 
72(84) ...
```

## License
MIT © [Michael Ruck](https://marsgasse.com)  
Source: [github.com/michaelruck/SkalenGenerator](https://github.com/michaelruck/SkalenGenerator)
