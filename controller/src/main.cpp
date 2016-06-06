#include "WProgram.h"
#include "xinput.h"

// Joystick axis positions
#define J_MIN    0
#define J_MIDDLE 512
#define J_MAX    1023

#define BUTTON_MIN 4  // First button
#define BUTTON_MAX 15 // Last button + 1


/*

    Pins mapping

        3              12  13
      0   1     8   9  10  11
        2       4   5   6   7      14

    XBox controller mapping

        ^         Back  Start
      <   >     X   Y  RB  LB
        v       A   B  RT  LT   Guide

*/
#define PIN_LEFT    0
#define PIN_RIGHT   1
#define PIN_DOWN    2
#define PIN_UP      3
#define PIN_A       4
#define PIN_B       5
#define PIN_X       8
#define PIN_Y       9
#define PIN_RB      10
#define PIN_LB      11
#define PIN_RT      6
#define PIN_LT      7
#define PIN_BACK    12
#define PIN_START   13
#define PIN_GUIDE   14


extern "C" int main(void)
{
    XINPUT controller(NO_LED);
    uint8_t state[BUTTON_MAX];

    // Configure joystick and button pins as inputs
    for (uint8_t i = 0; i < BUTTON_MAX; i++) {
        pinMode(i, INPUT_PULLUP);
    }

    while (true) {
        // Read button states
        for (uint8_t i = 0; i < BUTTON_MAX; ++i) {
            state[i] = !digitalReadFast(i);
        }

        // Update the DPAD
        controller.dpadUpdate(
            state[PIN_UP],
            state[PIN_DOWN],
            state[PIN_LEFT],
            state[PIN_RIGHT]);

        // Buttons
        controller.buttonUpdate(BUTTON_A, state[PIN_A]);
        controller.buttonUpdate(BUTTON_B, state[PIN_B]);
        controller.buttonUpdate(BUTTON_X, state[PIN_X]);
        controller.buttonUpdate(BUTTON_Y, state[PIN_Y]);
        controller.buttonUpdate(BUTTON_RB, state[PIN_RB]);
        controller.buttonUpdate(BUTTON_LB, state[PIN_LB]);
        controller.buttonUpdate(BUTTON_START, state[PIN_START]);
        controller.buttonUpdate(BUTTON_BACK, state[PIN_BACK]);
        controller.buttonUpdate(BUTTON_LOGO, state[PIN_GUIDE]);


        // Triggers
        uint8_t leftTrigger = 0;
        uint8_t rightTrigger = 0;
        if (state[PIN_LT]) { leftTrigger = 0xFF; }
        if (state[PIN_RT]) { rightTrigger = 0xFF; }
        controller.triggerUpdate(leftTrigger, rightTrigger);

        // Send data
        controller.sendXinput();

        // Receive data
        controller.receiveXinput();
    }
}
