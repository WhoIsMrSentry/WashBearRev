#include "Revolver.h"

RevolverController::RevolverController() {
}

void RevolverController::begin() {
    // Configure pinMode and initial state here
    pinMode(BUTTON_PIN_1, INPUT_PULLUP);
    pinMode(BUTTON_PIN_2, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
}

void RevolverController::update() {
    // Periodic control and button polling logic
}

bool RevolverController::buttonPressed() {
    // Buttons are wired as INPUT_PULLUP; pressed -> LOW
    return (digitalRead(BUTTON_PIN_1) == LOW) || (digitalRead(BUTTON_PIN_2) == LOW);
}

void RevolverController::signalActivity() {
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState ? HIGH : LOW);
}
