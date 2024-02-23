#include "SparkFunBME280.h"
#include "SparkFunCCS811.h"
#include "Adafruit_LTR390.h"
#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LIS2MDL.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <Wire.h>
#include <SD.h>

#define CCS811_ADDR 0x5B

CCS811 ccs(CCS811_ADDR);
BME280 bme;
Adafruit_LTR390 ltr = Adafruit_LTR390();
Adafruit_LSM303_Accel_Unified lsm303 = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LIS2MDL lis2mdl = Adafruit_LIS2MDL(12345);

char ccs811_tvoc[16];
char ccs811_co2[16];
char bme280_temp[16];
char bme280_humidity[16];
char bme280_pressure[16];
char bme280_altitude[16];
char ltr390_uv[16];
char lsm303_ax[16];
char lsm303_ay[16];
char lsm303_az[16];
char lis2mdl_mx[16];
char lis2mdl_my[16];
char lis2mdl_mz[16];
char nano_millis[32];

File myFile;

long delayMS = 25;
void setup() {
  Serial.begin(115200);
  Wire.begin();

  ccs.begin();

  bme.beginI2C();

  ltr.begin();
  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);

  lis2mdl.begin();
  lis2mdl.enableAutoRange(true);

  lsm303.begin();
  lsm303.setRange(LSM303_RANGE_4G);
  lsm303.setMode(LSM303_MODE_NORMAL);

  pinMode(10, OUTPUT);
  SD.begin(10);
}

char buffer[20];

void loop() {

  ccs.readAlgorithmResults();
  sensors_event_t magnetometerEvent;
  sensors_event_t accelerometerEvent;
  lis2mdl.getEvent(&magnetometerEvent);
  lsm303.getEvent(&accelerometerEvent);

  createIntegerPacket(ccs.getTVOC(), "C0:", ccs811_tvoc);
  createIntegerPacket(ccs.getCO2(), "C1:", ccs811_co2);
  createFloatPacket(bme.readTempC(), "E0:", bme280_temp);
  createFloatPacket(bme.readFloatHumidity(), "E1:", bme280_humidity);
  createFloatPacket(bme.readFloatPressure(), "E2:", bme280_pressure);
  createFloatPacket(bme.readFloatAltitudeFeet(), "E3:", bme280_altitude);
  createIntegerPacket(ltr.readUVS(), "T0:", ltr390_uv);
  createFloatPacket(accelerometerEvent.acceleration.x, "S0:", lsm303_ax);
  createFloatPacket(accelerometerEvent.acceleration.y, "S1:", lsm303_ay);
  createFloatPacket(accelerometerEvent.acceleration.z, "S2:", lsm303_az);
  createFloatPacket(magnetometerEvent.magnetic.x, "S3:", lis2mdl_mx);
  createFloatPacket(magnetometerEvent.magnetic.y, "S4:", lis2mdl_my);
  createFloatPacket(magnetometerEvent.magnetic.z, "S5:", lis2mdl_mz);
  createIntegerPacket((int)millis(), "N0:", nano_millis);

  // myFile = SD.open("test.txt", FILE_WRITE);
  // myFile.println(ccs811_tvoc);
  // myFile.close();

  delay(1000);
}

void createIntegerPacket(int integer, char identifier[3], char* packetString){
  memset(buffer, 0, sizeof(buffer));
  memset(packetString, 0, sizeof(packetString));
  strcpy(packetString, identifier);
  itoa(integer, buffer, 10);
  strcat(packetString, buffer);
  strcat(packetString, ";");

  Serial.println(packetString);
}

void createFloatPacket(float floatValue, char identifier[3], char* packetString){
  memset(buffer, 0, sizeof(buffer));
  memset(packetString, 0, sizeof(packetString));
  strcpy(packetString, identifier);
  dtostrf(floatValue, 10, 2, buffer);
  strcat(packetString, buffer);
  strcat(packetString, ";");

  Serial.println(packetString);
}