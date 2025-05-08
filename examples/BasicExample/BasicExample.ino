#include <SkalenGenerator.h>

SkalenGenerator scaleGen;
uint8_t scale[128];

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
    delay(100);
  }
  digitalWrite(BUILTIN_LED, 0);

  // Generiere C-Dur-Skala
  uint8_t basePos = scaleGen.generateScale(scale, 60, IONIAN);

  // Ausgabe mit Serial.printf()
  Serial.printf("\n=== C-Dur im gesamten MIDI-Bereich ===\n");
  Serial.printf("Anzahl Noten: %d\n", scaleGen.totalNotes);
  Serial.printf("Position der Basisnote (C4): %d\n", basePos);
  Serial.printf("Noten (gruppiert nach Oktaven):\n");

  // Oktavweise Ausgabe
  for (uint8_t i = 0; i < scaleGen.totalNotes; i++) {
    // Markiere Basisnote mit Klammern
    const char* format = (i == basePos) ? "(%3d)" : "%4d";
    
    Serial.printf(format, scale[i]);
    
    // Zeilenumbruch nach 7 Noten (Oktavende)
    if ((i + 1) % 7 == 0 || i == scaleGen.totalNotes - 1) {
      Serial.printf(",\n");
    } else {
      Serial.printf(", ");
    }
  }
}

void loop() {}
