#include "WProgram.h"

// Joystick axis positions
#define J_MIN    0
#define J_MIDDLE 512
#define J_MAX    1023

#define BUTTON_MIN 8  // First button
#define BUTTON_MAX 34 // Last button + 1

extern "C" int main(void)
{
    Joystick.useManualSend(true);

    // Configure joystick an button pins as inputs
    for (int i = 0; i < BUTTON_MAX; i++) {
        pinMode(i, INPUT_PULLUP);
    }

    while (true) {
        unsigned int x1 = J_MIDDLE;
        unsigned int y1 = J_MIDDLE;
        unsigned int x2 = J_MIDDLE;
        unsigned int y2 = J_MIDDLE;

        // Read joystick positions
        for (uint8_t i = 0; i < BUTTON_MIN; ++i) {
            if (!digitalReadFast(i)) {
                switch (i) {
                  case 0:
                    x1 = J_MIN;
                    break;
                  case 1:
                    x1 = J_MAX;
                    break;
                  case 2:
                    y1 = J_MIN;
                    break;
                  case 3:
                    y1 = J_MAX;
                    break;
                  case 4:
                    x2 = J_MIN;
                    break;
                  case 5:
                    x2 = J_MAX;
                    break;
                  case 6:
                    y2 = J_MIN;
                    break;
                  case 7:
                    y2 = J_MAX;
                    break;
                }
            }
        }

        Joystick.X(x1);
        Joystick.Y(y1);
        Joystick.Z(x2);
        Joystick.Zrotate(y2);

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
