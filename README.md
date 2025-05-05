# SkalenGenerator Arduino Library
Generiert Tonleitern und Jazz-Skalen als MIDI-Noten für Musikprojekte.

## Funktionen
- Unterstützt **17+ Skalen** (Dur, Moll, Blues, Bebop, Modi, etc.).
- Einfache Integration in MIDI-Synthesizer oder Musik-Apps.
- Optimiert für Arduino (mit `PROGMEM` für Speichereffizienz).

## Installation
1. **Herunterladen**: [ZIP herunterladen](https://github.com/michaelruck/SkalenGenerator/archive/refs/heads/main.zip).
2. **Installieren**: In der Arduino-IDE unter `Sketch → Include Library → Add .ZIP Library` auswählen.
3. **Beispiele finden** unter `File → Examples → SkalenGenerator`.

## Verwendung
```cpp
#include <SkalenGenerator.h>

SkalenGenerator scaleGen;
uint8_t scale[12];

void setup() {
  scaleGen.generateScale(scale, 60, IONIAN); // C-Dur generieren
}

Unterstützte Skalen
Skala	Beispiel (C)
IONIAN (Dur)	C, D, E, F, G, A, B
DORIAN	C, D, Eb, F, G, A, Bb
BLUES	C, Eb, F, F#, G, Bb
ALTERED	C, Db, Eb, E, Gb, Ab, Bb
