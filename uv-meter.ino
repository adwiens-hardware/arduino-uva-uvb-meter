// Include the SparkFun VEML6075 library.
// Click here to get the library: http://librarymanager/All#SparkFun_VEML6075
#include <SparkFun_VEML6075_Arduino_Library.h>

#define NUM_SAMPLES (300.0) /* 500 ~ 1.5s */

const float UVA_RES = 0.93; // responsivity in counts/(uW/cm^2) @ 50ms integration time from datasheet
const float UVB_RES = 2.1;

VEML6075 uv; // Create a VEML6075 object

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  while (!uv.begin()) delay(1000);
  uv.setIntegrationTime(VEML6075::IT_50MS); // 50ms
  Serial.println("UVB(uW/cm2) UVA(uW/cm2) uvcomp1 uvcomp2");
}

void loop()
{
  float uvb = 0, uva = 0, uvcomp1 = 0, uvcomp2 = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    uva += uv.rawUva(); // side note: this is half as fast as it could be, because
    uvb += uv.rawUvb(); // each takes a sample.
    uvcomp1 += uv.uvComp1();
    uvcomp2 += uv.uvComp2();
  }
  uva = uva / NUM_SAMPLES / UVA_RES; // take the average of many samples
  uvb = uvb / NUM_SAMPLES / UVB_RES;
  uvcomp1 /= NUM_SAMPLES; // if the uvcomp's are small enough, they can be ignored
  uvcomp2 /= NUM_SAMPLES;
  Serial.println(String(uvb) + "," + String(uva) + "," + String(uvcomp1) + "," + String(uvcomp2));
}
