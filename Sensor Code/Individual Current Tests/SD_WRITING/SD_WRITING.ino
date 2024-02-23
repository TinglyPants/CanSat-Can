#include <SD.h>
#include <SPI.h>

File myFile;

void setup() {
  pinMode(10, OUTPUT);
  Serial.begin(115200);

  if (!SD.begin(10)) {
    Serial.println("initialization failed!"); // SD card needs 5V, remember to use 5V not 3.3
    return;
  }
  Serial.println("initialization done.");
}
unsigned long count = 0;

void loop() {
  count++;
  myFile = SD.open("test.txt", FILE_WRITE);
  myFile.println(count);
  myFile.close();
  Serial.println("wrote to SD!");
  delay(25);
}
