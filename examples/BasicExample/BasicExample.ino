#include <SkalenGenerator.h>

SkalenGenerator scaleGen;
uint8_t scale[128];
uint8_t totalNotes = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(1); };

  scaleGen.generateScale(scale, 60, IONIAN, totalNotes);

  Serial.println("=== C-Dur im gesamten MIDI-Bereich ===");
  Serial.printf("Anzahl Noten: %d\r\n", totalNotes);
  for (uint8_t i = 0; i < totalNotes; i++) {
    Serial.printf("%3d", scale[i]);
    if (i < totalNotes - 1) Serial.print(", ");
    if ((i+1) % 8 == 0) Serial.println();
  }
}

void loop() {}
