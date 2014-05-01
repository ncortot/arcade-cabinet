/*
    SmartMatrix Features Demo - Louis Beaudoin (Pixelmatix)
    This example code is released into the public domain
*/

#include <Arduino.h>
#include "SmartMatrix.h"

SmartMatrix matrix;

const int defaultBrightness = 100*(255/100);    // full brightness
//const int defaultBrightness = 15*(255/100);    // dim: 15% brightness
const int defaultScrollOffset = 6;
const rgb24 defaultBackgroundColor = {0x40, 0, 0};

// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;

// the setup() method runs once, when the sketch starts
void setup() {
    // initialize the digital pin as an output.
    pinMode(ledPin, OUTPUT);

    Serial.begin(38400);

    matrix.begin();
    matrix.setBrightness(defaultBrightness);

    matrix.setScrollOffsetFromEdge(defaultScrollOffset);

    matrix.setColorCorrection(cc24);
}

// the loop() method runs over and over again,
// as long as the board has power
void loop() {
    int i;
    unsigned long currentMillis;

    // clear screen
    matrix.fillScreen(defaultBackgroundColor);
    matrix.swapBuffers(true);

    // "Drawing Pixels"
    {
        // "Drawing Functions"
        matrix.setScrollColor({0xff, 0xff, 0xff});
        matrix.setScrollMode(wrapForward);
        matrix.setScrollSpeed(40);
        matrix.setScrollFont(font6x10);
        // matrix.scrollText("Pixels", 1);

        const uint transitionTime = 3000;

        matrix.fillScreen({0, 0, 0});
        matrix.swapBuffers(true);

        currentMillis = millis();

        while (millis() - currentMillis < transitionTime) {
            int x0, y0;

            rgb24 color;
            float fraction = ((float)millis() - currentMillis) / ((float)transitionTime / 2);

            if (millis() - currentMillis < transitionTime / 2) {
                color.red = 255 - 255.0 * fraction;
                color.green = 255.0 * fraction;
                color.blue = 0;
            }
            else {
                color.red = 0;
                color.green = 255 - 255.0 / 2 * (fraction - 1.0);
                color.blue = 255.0 * (fraction - 1.0);
            }

            for (i = 0; i < 20; i++) {
                x0 = random(matrix.getScreenWidth());
                y0 = random(matrix.getScreenHeight());

                matrix.drawPixel(x0, y0, color);
            }
            matrix.swapBuffers(true);
        }
    }

    // "Drawing Lines"
    {
        matrix.setScrollColor({0xff, 0xff, 0xff});
        matrix.setScrollMode(wrapForward);
        matrix.setScrollSpeed(40);
        matrix.setScrollFont(font6x10);
        // matrix.scrollText("Horizontal and Vertical Lines", 1);

        int transitionTime = 6000;

        //matrix.fillScreen({0, 0, 0});
        //matrix.swapBuffers(true);

        currentMillis = millis();
        unsigned long delayCounter = currentMillis;

        for (i = 0; i < matrix.getScreenWidth(); i++) {
            rgb24 color;
            float fraction = ((float)millis() - currentMillis) / ((float)transitionTime / 2);

            color.red = 255 - 255.0 * fraction;
            color.green = 255.0 * fraction;
            color.blue = 0;

            matrix.drawFastVLine(i, 0, matrix.getScreenHeight(), color);
            matrix.swapBuffers(true);
            delayCounter += transitionTime / 2 / matrix.getScreenWidth();
            while (millis() < delayCounter);
        }

        for (i = 0; i < matrix.getScreenHeight(); i++) {
            rgb24 color;
            float fraction = ((float)millis() - currentMillis) / ((float)transitionTime / 2);
            fraction -= 1.0;
            if (fraction < 0) fraction = 0.0;

            color.red = 0;
            color.green = 255 - 255.0 / 2 * (fraction);
            color.blue = 255.0 * (fraction);

            matrix.drawFastHLine(0, matrix.getScreenWidth(), i, color);
            matrix.swapBuffers(true);
            delayCounter += transitionTime / 2 / matrix.getScreenHeight();
            while (millis() < delayCounter);
        }

        // matrix.scrollText("Diagonal Lines", 1);

        transitionTime = 4000;
        currentMillis = millis();
        delayCounter = currentMillis;

        for (i = 0; i < matrix.getScreenWidth() * 2; i++) {
            rgb24 color;
            float fraction = ((float)millis() - currentMillis) / ((float)transitionTime / 2);

            color.red = 255 - 255.0 * fraction;
            color.green = 255.0 * fraction;
            color.blue = 0;

            matrix.drawLine(i, 0, 0, i, color);
            matrix.swapBuffers(true);
            delayCounter += transitionTime / 2 / (matrix.getScreenWidth() * 2);
            while (millis() < delayCounter);
        }

        for (i = 0; i < matrix.getScreenWidth() * 2; i++) {
            rgb24 color;
            float fraction = ((float)millis() - currentMillis) / ((float)transitionTime / 2);
            fraction -= 1.0;
            if (fraction < 0) fraction = 0.0;

            color.red = 0;
            color.green = 255 - 255.0 / 2 * (fraction);
            color.blue = 255.0 * (fraction);

            matrix.drawLine(0, matrix.getScreenHeight() - i, matrix.getScreenWidth(), i, color);
            matrix.swapBuffers(true);
            delayCounter += transitionTime / 2 / (matrix.getScreenWidth() * 2);
            while (millis() < delayCounter);
        }
    }

    // draw bitmap
    {
        const int testBitmapWidth = 15;
        const int testBitmapHeight = 15;
        uint8_t testBitmap[] = {
            _______X, ________,
            ______XX, X_______,
            ______XX, X_______,
            ______XX, X_______,
            _____XXX, XX______,
            XXXXXXXX, XXXXXXX_,
            _XXXXXXX, XXXXXX__,
            __XXXXXX, XXXXX___,
            ___XXXXX, XXXX____,
            ____XXXX, XXX_____,
            ___XXXXX, XXXX____,
            ___XXXX_, XXXX____,
            __XXXX__, _XXXX___,
            __XX____, ___XX___,
            __X_____, ____X___,
        };

        // "Drawing Functions"
        matrix.setScrollColor({0xff, 0xff, 0xff});
        matrix.setScrollMode(wrapForward);
        matrix.setScrollSpeed(40);
        matrix.setScrollFont(font6x10);
        // matrix.scrollText("Mono Bitmaps", 1);

        const uint transitionTime = 5500;
        currentMillis = millis();

        matrix.fillScreen({0, 0x80, 0x80});
        matrix.swapBuffers(true);

        while (millis() < currentMillis + transitionTime) {
            matrix.drawMonoBitmap(random(matrix.getScreenWidth() + testBitmapWidth) - testBitmapWidth,
                                  random(matrix.getScreenHeight() + testBitmapHeight) - testBitmapHeight,
                                  testBitmapWidth, testBitmapHeight, {(uint8_t)random(256), (uint8_t)random(256), 0}, testBitmap);
            matrix.swapBuffers(true);
            delay(100);
        }
    }

}
