/*
LSM303AGR sensor test, designed for testing current draw.
Change delay time and get values then, as not sure what delay will be used in final test.
Part of the UKSA CanSat project
Matthew WL Chalk 2023
*/

#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LIS2MDL.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_LSM303_Accel_Unified lsm303 = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LIS2MDL lis2mdl = Adafruit_LIS2MDL(12345);

long delayMS = 100;

void setup() {
  // Serial Initiation•
  Serial.begin(115200);

  // Initiate Magnetometer
  if (!lis2mdl.begin()) {
    Serial.println("lis2mdl init failure.");
    while(1){};
  }
  lis2mdl.enableAutoRange(true);

  // Initiate Accelerometer 
  if (!lsm303.begin()) {
    Serial.println("lsm303 init failure.");
  }
  lsm303.setRange(LSM303_RANGE_4G);
  lsm303.setMode(LSM303_MODE_NORMAL);
}

void loop() {
  // Gather Sensor Data
  sensors_event_t magnetometerEvent;
  sensors_event_t accelerometerEvent;

  lis2mdl.getEvent(&magnetometerEvent);
  lsm303.getEvent(&accelerometerEvent);

  // Display Sensor Data
  Serial.print("MX: ");
  Serial.println(magnetometerEvent.magnetic.x);
  Serial.print("MY: ");
  Serial.println(magnetometerEvent.magnetic.y);
  Serial.print("MZ: ");
  Serial.println(magnetometerEvent.magnetic.z);

  Serial.print("AX: ");
  Serial.println(accelerometerEvent.acceleration.x);
  Serial.print("AY: ");
  Serial.println(accelerometerEvent.acceleration.y);
  Serial.print("AZ: ");
  Serial.println(accelerometerEvent.acceleration.z);

  delay(delayMS);
}
