/*!
 * @file veml6075_simple.ino
 *
 * A basic test of the sensor with default settings
 * 
 * Designed specifically to work with the VEML6075 sensor from Adafruit
 * ----> https://www.adafruit.com/products/3964
 *
 * These sensors use I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface with the breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */
 
#include <Wire.h>
#include "Adafruit_VEML6075.h"

#define NUM_SAMPLES (150.0) /* 150 ~ 1.0s */

const double UVA_RES = 0.93 / 0.5016286645; // responsivity in counts/(uW/cm^2) @ 50ms integration time from datasheet scaled by value from SparkFun_VEML6075_Arduino_Library.cpp to get equivalent for 100ms
const double UVB_RES = 2.1 / 0.5016286645;

Adafruit_VEML6075 uv = Adafruit_VEML6075();

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  Serial.println("VEML6075 UVA & UVB Meter");
  while (!uv.begin()) {
    Serial.println("Unable to communicate with VEML6075. Retrying...");
    delay(1000);
  }
  Serial.println("Found VEML6075 sensor");
}


int loopCtr = 0;
void loop()
{
  double uvb = 0, uva = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    uva += uv.readUVA(); // side note: this is half as fast as it could be, because
    uvb += uv.readUVB(); // each read takes a new sample.
  }
  uva = uva / NUM_SAMPLES / UVA_RES; // take the average of many samples
  uvb = uvb / NUM_SAMPLES / UVB_RES;
  if (loopCtr++ % 25 == 0) {
    Serial.println("UVB(uW/cm^2) UVA(uW/cm^2)");
  }
  Serial.println(String(uvb) + " " + String(uva));
}
