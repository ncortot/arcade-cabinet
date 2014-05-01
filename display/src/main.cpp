#include <WProgram.h>

extern "C" int main(void)
{
    setup();
    for (;;) {
        loop();
    }
}
