// Revolver controller skeleton
#ifndef REVOLVER_H
#define REVOLVER_H

// Default pin assignments used by the original sketch
static const int BUTTON_PIN_1 = 3;
static const int BUTTON_PIN_2 = 4;
static const int LED_PIN = 13;

class RevolverController {
public:
    RevolverController();
    void begin();
    void update();
    bool buttonPressed();
    void signalActivity();
private:
    // hardware pins and state can be stored here
    bool blinkState = false;
};

#endif // REVOLVER_H
