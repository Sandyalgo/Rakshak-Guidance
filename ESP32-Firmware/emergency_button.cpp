#include "emergency_button.h"
#include "main.h"
#include "Arduino.h"
// --- Debounce configuration ---
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200; // 200 ms debounce

void init_emergency_button_system(void)
{
    pinMode(EMERGENCY_BUTTON_PIN, INPUT_PULLDOWN);  // internal pulldown resistor
    Serial.println("Emergency button system initialized.");
}

bool is_emergency_pressed(void)
{
    int buttonState = digitalRead(EMERGENCY_BUTTON_PIN);

    if (buttonState == HIGH)
    {
        Serial.println("Button Pressed (HIGH)");
        return true;
    }
    else
    {
        return false;
    }
}

