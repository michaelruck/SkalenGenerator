#include <SkalenGenerator.h>

SkalenGenerator scaleGen;
uint8_t scale[128];
uint8_t currentScale = IONIAN;
uint8_t rootNote = 60; // C4

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    while (!Serial) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(100);
    }
    digitalWrite(LED_BUILTIN, LOW);

    Serial.println("\n=== Skalen Generator ===");
    printMenu();
}

void loop() {
    if (Serial.available()) {
        handleInput(Serial.read());
    }
}

void printMenu() {
    Serial.println("\nVerfügbare Skalen:");
    SkalenGenerator::printAvailableScales();
    Serial.printf("\nAktuell: %s (MIDI %d)\n", 
        SkalenGenerator::getScaleInfo(currentScale)->name,
        rootNote);
    Serial.println("Eingabe: 0-16=Skala, +=Oktave hoch, -=Oktave runter, ?=Hilfe");
}

void handleInput(char c) {
    if (c >= '0' && c <= '9') {
        uint8_t num = c - '0';
        if (num < SCALE_COUNT) {
            currentScale = (ScaleType)num;
            generateAndPrint();
        }
    } else if (c == '+' || c == '-') {
        rootNote = constrain(rootNote + (c == '+' ? 12 : -12), 0, 127);
        generateAndPrint();
    } else if (c == '?') {
        printMenu();
    }
}

void generateAndPrint() {
    uint8_t basePos = scaleGen.generateScale(scale, rootNote, currentScale);
    
    Serial.printf("\n=== %s (MIDI %d) ===\n", 
        SkalenGenerator::getScaleInfo(currentScale)->name,
        rootNote);
    Serial.printf("Noten (%d):\n", scaleGen.totalNotes);
    
    for (uint8_t i = 0; i < scaleGen.totalNotes; i++) {
        if (i == basePos) Serial.printf("(%3d)", scale[i]);
        else Serial.printf("%4d", scale[i]);
        
        if ((i + 1) % 7 == 0 || i == scaleGen.totalNotes - 1) Serial.println();
        else Serial.print(", ");
    }
}
