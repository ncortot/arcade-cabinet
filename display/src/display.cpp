#include <Arduino.h>
#include "SmartMatrix.h"

SmartMatrix matrix;

const int defaultBrightness = 255;
const int defaultScrollOffset = 6;
const rgb24 defaultBackgroundColor = {0, 0, 0};

void displaySetup() {
    matrix.begin();
    matrix.setBrightness(defaultBrightness);
    matrix.setScrollOffsetFromEdge(defaultScrollOffset);
    matrix.setColorCorrection(cc24);
}

void displayLoop() {
    // clear screen
    matrix.fillScreen(defaultBackgroundColor);
    matrix.swapBuffers(true);

    // MP lines
    const int lineY[] = {1, 4, 7, 10, 13};
    const int lineX[] = {-8, -4, 0, -4, -8};
    const rgb24 lineColor[] = {
        {0xFC, 0xCC, 0x2E},
        {0xEC, 0x39, 0x94},
        {0xAE, 0x4F, 0x93},
        {0x31, 0x88, 0xBE},
        {0x21, 0xAB, 0x77}
    };
    const int length = 60;

    int posX = 0;
    while (posX < 200) {
        for (int line = 0; line < 5; line++) {
            int x = posX + lineX[line];
            int y = lineY[line];
            rgb24 color = lineColor[line];

            matrix.drawPixel(x, y - 1, color);
            matrix.drawPixel(x, y, color);
            matrix.drawPixel(x, y + 1, color);

            matrix.drawPixel(x - 3, y - 1, defaultBackgroundColor);
            matrix.drawPixel(x - 3, y + 1, defaultBackgroundColor);
            matrix.drawPixel(x - length, y, defaultBackgroundColor);
        }
        delay(20);
        matrix.swapBuffers(true);
        posX++;
    }

    rgb24 startGradient = {0xFC, 0xCC, 0x2E};
    rgb24 endGradient = {0xAE, 0x4F, 0x93};
    matrix.setFont(font6x10);

    const char* text = "MULTIPOSTING";
    int xFirst = MATRIX_WIDTH - 1;
    while (true) {
        matrix.fillScreen(defaultBackgroundColor);

        int xCur = xFirst;
        // limit text to 10 chars, why?
        for (uint8_t i = 0; i < strlen(text); ++i) {
            int yCur = 5 * sin(xCur * 8 * PI / MATRIX_WIDTH) + 3;
            rgb24 color;
            color.red = startGradient.red + (endGradient.red - startGradient.red)
                * (xCur + apple6x10.Width) / (MATRIX_WIDTH + apple6x10.Width);
            color.green = startGradient.green + (endGradient.green - startGradient.green)
                * xCur / MATRIX_WIDTH;
            color.blue = startGradient.blue + (endGradient.blue - startGradient.blue)
                * xCur / MATRIX_WIDTH;
            matrix.drawChar(xCur, yCur, color, text[i]);

            xCur += apple6x10.Width;
            if (xCur >= MATRIX_WIDTH) {
                break;
            }
        }

        matrix.swapBuffers(true);
        delay(60);
        xFirst -= 1;
        if (xCur < 0) {
            break;
        }
    }

}
