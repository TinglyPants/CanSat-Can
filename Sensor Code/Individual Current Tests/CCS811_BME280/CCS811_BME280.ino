/*
CCS811 and BME280 sensor tests for measuring current draw.
Part of the UKSA CanSat project
Matthew WL Chalk 2023
*/

#include "SparkFunBME280.h"
#include "SparkFunCCS811.h"
#include <Wire.h>

#define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address

CCS811 ccs(CCS811_ADDR);
BME280 bme;

long delayMS = 100;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!ccs.begin())
  {
    Serial.println("CCS811 init failed");
  }

  if (!bme.beginI2C())
  {
    Serial.println("CCS811 init failed");
  }

}

void loop() {

  //BME280
  Serial.println(" Humidity (unknown unit): ");
  Serial.println(bme.readFloatHumidity());

  Serial.println(" Pressure (hPa): ");
  Serial.println(bme.readFloatPressure());

  Serial.println(" Temp (C): ");
  Serial.println(bme.readTempC());
  
  //CCS811
  ccs.readAlgorithmResults();

  Serial.println(" TVOC (ppb): ");
  Serial.println(ccs.getTVOC());

  Serial.println(" CO2 (ppm): ");
  Serial.println(ccs.getCO2());

  delay(delayMS);

}
