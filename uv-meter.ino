// Include the SparkFun VEML6075 library.
// Click here to get the library: http://librarymanager/All#SparkFun_VEML6075
#include <SparkFun_VEML6075_Arduino_Library.h>

#define NUM_SAMPLES (500.0) /* 500 ~ 1.5s */

const double UVA_RES = 0.93 / 0.5016286645; // responsivity in counts/(uW/cm^2) @ 50ms integration time from datasheet scaled by value from SparkFun_VEML6075_Arduino_Library.cpp to get equivalent for 100ms
const double UVB_RES = 2.1 / 0.5016286645;

VEML6075 uv; // Create a VEML6075 object

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  while (!uv.begin()) {
    Serial.println("Unable to communicate with VEML6075. Retrying...");
    delay(1000);
  }
}

int loopCtr = 0;
void loop()
{
  double uvb = 0, uva = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    uva += uv.uva(); // side note: this is half as fast as it could be, because
    uvb += uv.uvb(); // uva() and uvb() each take a sample.
  }
  uva = uva / NUM_SAMPLES / UVA_RES; // take the average of many samples
  uvb = uvb / NUM_SAMPLES / UVB_RES;
  if (loopCtr++ % 25 == 0) {
    Serial.println("UVB(uW/cm^2) UVA(uW/cm^2)");
  }
  Serial.println(String(uvb) + " " + String(uva));
}
