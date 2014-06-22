#include "WProgram.h"

// Joystick axis positions
#define J_MIN    0
#define J_MIDDLE 512
#define J_MAX    1023

#define BUTTON_MIN 4  // First button
#define BUTTON_MAX 24 // Last button + 1

extern "C" int main(void)
{
    Joystick.useManualSend(true);

    // Configure joystick and button pins as inputs
    for (int i = 0; i < BUTTON_MAX; i++) {
        pinMode(i, INPUT_PULLUP);
    }

    while (true) {
        unsigned int x = J_MIDDLE;
        unsigned int y = J_MIDDLE;

        // Read joystick positions
        for (uint8_t i = 0; i < BUTTON_MIN; ++i) {
            if (!digitalReadFast(i)) {
                switch (i) {
                  case 0:
                    x = J_MIN;
                    break;
                  case 1:
                    x = J_MAX;
                    break;
                  case 2:
                    y = J_MAX;
                    break;
                  case 3:
                    y = J_MIN;
                    break;
                }
            }
        }

        Joystick.X(x);
        Joystick.Y(y);

        // Read button states
        for (uint8_t i = BUTTON_MIN; i < BUTTON_MAX; ++i) {
            bool state = !digitalReadFast(i);
            Joystick.button(i - BUTTON_MIN + 1, state);
        }

        // Send new state
        Joystick.send_now();

        delay(5);
        yield();
    }
}
