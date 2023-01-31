/*

Example for ESP_8_BIT color composite video generator library on ESP32.
Connect GPIO25 to signal line, usually the center of composite video plug.

GFX Hello World

This demonstrates using the ESP_8_BIT_GFX class, which inherits from the
Adafruit GFX base class to deliver an easy to use graphics API. Draws two
rectangles that cycle around the border of the screen. The amount of corners
cut off from these rectangle show the amount of overscan on a particular
screen. In the middle of two rectangles are a bit of text drawn using
Adafruit GFX print() API.

Copyright (c) Roger Cheng

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <ESP_8_BIT_GFX.h>

#include <ESP32Time.h>


// Create an instance of the graphics library
ESP_8_BIT_GFX videoOut(0 /* = PAL */, 8 /* = RGB332 color */);


ESP32Time rtc(3600);  // offset in seconds GMT+1

void setup() {
  // Initial setup of graphics library
  videoOut.begin();

  rtc.setTime(22, 10, 17, 30, 1, 2022);  // 17th Jan 2021 15:24:30
}

void loop() {
  // Wait for the next frame to minimize chance of visible tearing
  videoOut.waitForFrame();

  // Get the current time and calculate a scaling factor
  unsigned long time = millis();
  // Clear screen
  videoOut.fillScreen(0);
  /*
  // Draw one rectangle
  videoOut.drawLine(movingX, 0,       255,     movingY, cycle);
  videoOut.drawLine(255,     movingY, invertX, 239,     cycle);
  videoOut.drawLine(invertX, 239,     0,       invertY, cycle);
  videoOut.drawLine(0,       invertY, movingX, 0,       cycle);

  // Draw a rectangle with inverted position and color
  videoOut.drawLine(invertX, 0,       255,     invertY, invertC);
  videoOut.drawLine(255,     invertY, movingX, 239,     invertC);
  videoOut.drawLine(movingX, 239,     0,       movingY, invertC);
  videoOut.drawLine(0,       movingY, invertX, 0,       invertC);
*/
  // Draw text in the middle of the screen
  videoOut.setCursor(0, 80);
  videoOut.setTextColor(0xFF);
  videoOut.setTextSize(9);
  videoOut.setTextWrap(false);
  videoOut.print(rtc.getTime("%H:%M"));
  delay(1000);
  
}
