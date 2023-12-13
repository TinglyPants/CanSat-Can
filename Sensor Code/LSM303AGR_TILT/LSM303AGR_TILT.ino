/*
LSM303AGR tilt tracking for flight path tracking and landing correction data.
Part of the UKSA CanSat project
Matthew WL Chalk 2023
*/
#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Raw Data
float X_out;
float Y_out;
float Z_out;

// Calculated roll & pitch
float roll;
float pitch;

// Low pass filtering
float rollF = 0;
float pitchF = 0;

// Assign a unique ID to this sensor at the same time 
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

void setup() {
  Serial.begin(9600);

  // Initiate Accelerometer
  if (!accel.begin()) {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
  }

  accel.setRange(LSM303_RANGE_4G);
  accel.setMode(LSM303_MODE_NORMAL);
}

void loop() {
  // Take Reading
  sensors_event_t event;
  accel.getEvent(&event);

  X_out = event.acceleration.x / 9.80665;
  Y_out = event.acceleration.y / 9.80665;
  Z_out = event.acceleration.z / 9.80665;

  // Calculate roll and pitch
  roll = atan(Y_out / sqrt(pow(X_out, 2) + pow(Z_out, 2))) * 180/PI;
  pitch = atan(-1 * X_out / sqrt(pow(Y_out, 2) + pow(Z_out, 2))) * 180/PI;

  // Low pass filter
  rollF = 0.90 * rollF + 0.1 * roll;
  pitchF = 0.90 * pitchF + 0.1 * pitch;

  Serial.print(rollF);
  Serial.print(",");
  Serial.println(pitchF);

  delay(50);
}
