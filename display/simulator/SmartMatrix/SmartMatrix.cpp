/*
 * SmartMatrix Library - Refresh Code for Teensy 3.x Platform
 *
 * Copyright (c) 2014 Louis Beaudoin (Pixelmatix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "SmartMatrix.h"
#include "CircularBuffer.h"

// these definitions may change if switching major display type
#define MATRIX_ROW_PAIR_OFFSET      (MATRIX_HEIGHT/2)
#define MATRIX_ROWS_PER_FRAME       (MATRIX_HEIGHT/2)
#define PIXELS_UPDATED_PER_CLOCK    2
#define COLOR_CHANNELS_PER_PIXEL    3
#define LATCHES_PER_ROW             (COLOR_DEPTH_RGB/COLOR_CHANNELS_PER_PIXEL)
#define DMA_UPDATES_PER_CLOCK       2

// hardware-specific definitions
// prescale of 0 is F_BUS
#define LATCH_TIMER_PRESCALE  0x00
#define NS_TO_TICKS(X)      (uint32_t)(F_BUS * ((X) / 1000000000.0))
#define LATCH_TIMER_PULSE_WIDTH_TICKS   NS_TO_TICKS(LATCH_TIMER_PULSE_WIDTH_NS)
#define TICKS_PER_ROW   (F_BUS/MATRIX_REFRESH_RATE/MATRIX_ROWS_PER_FRAME)
#define MSB_BLOCK_TICKS     (TICKS_PER_ROW/2)
// the MIN_BLOCK_PERIOD_NS is configured for one 32px panel
#define MIN_BLOCK_PERIOD_TICKS  NS_TO_TICKS(MIN_BLOCK_PERIOD_NS * MATRIX_WIDTH / 32)


/*
  buffer contains:
    COLOR_DEPTH/sizeof(int32_t) * 2 words for each pair of pixels (pixel data from n, and n+MATRIX_ROW_PAIR_OFFSET)
      first half of the words contain a byte for each shade, going from LSB to MSB
      second half of the words have the same data, plus a high bit in each byte for the clock
    there are MATRIX_WIDTH number of these in order to refresh a row (pair of rows)
 */

SmartMatrix::SmartMatrix() {

}

void SmartMatrix::begin()
{
}

void SmartMatrix::updateForRead()
{
    handleBufferSwap();
    updateForeground();
}
