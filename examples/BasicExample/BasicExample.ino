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

/* Output:
=== C-Dur im gesamten MIDI-Bereich ===
Anzahl Noten: 73
  0,   2,   3,   5,   7,   9,  10,  12, 
 14,  16,  17,  19,  21,  23,  24,  26, 
 28,  30,  31,  33,  35,  37,  38,  40, 
 42,  44,  45,  47,  49,  51,  52,  54, 
 56,  58,  60,  62,  63,  65,  67,  69, 
 70,  72,  74,  76,  77,  79,  81,  83, 
 84,  86,  88,  90,  91,  93,  95,  97, 
 98, 100, 102, 104, 105, 107, 109, 111, 
112, 114, 116, 118, 119, 121, 123, 125, 
126
*/
