#include <WProgram.h>
#include "display.h"

extern "C" int main(void)
{
    displaySetup();
    for (;;) {
        displayLoop();
    }
}
