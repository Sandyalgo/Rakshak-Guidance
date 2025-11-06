#ifndef EMERGENCY_BUTTON_SYSTEM_H
#define EMERGENCY_BUTTON_SYSTEM_H

#define EMERGENCY_BUTTON_PIN 25 

void init_emergency_button_system(void);
bool is_emergency_pressed(void);
void handle_emergency_button(void);

#endif

