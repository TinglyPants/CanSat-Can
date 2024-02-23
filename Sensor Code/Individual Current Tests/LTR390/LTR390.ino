// I have lost all sense of meaning

#include "Adafruit_LTR390.h"
#include <Wire.h>

Adafruit_LTR390 ltr = Adafruit_LTR390();

unsigned long delayMS = 25;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if ( ! ltr.begin() ) 
  {
    Serial.println("Couldn't find LTR sensor!");
    while (1); //Freeze
  }

  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);
}

void loop() {
  Serial.println(" UV data: "); 
  Serial.println(ltr.readUVS());


  delay(delayMS);
}
