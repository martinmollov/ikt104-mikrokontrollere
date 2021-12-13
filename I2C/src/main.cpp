#include <Arduino.h>
#include <Wire.h>
#include "functs.h"

// HTS221 I2C address is 0x5F
#define Addr 0x5F
int LEDgreen = A0;
int LEDred = A1;

void setup() {
// Wait 10 seconds so we have time to open the serial monitor
delay(10000);
// OK
Serial.println("OK");
// Initialize Serial library
Serial.begin(9600);
// Initialize I2C library
Wire.begin();
// Turn on sensor
write2(0x20, 0x81);
}

void loop() {
// Start a measurement.
write2(0x21, 0x01);
// Wait for the measurement to finished.
delay(5000);
// Point to HUMIDITY_OUT_L, HUMIDITY_OUT_H.
read_hum(0x5F, 1, 0x28, 1, 0x29);
read_temp(0x5F, 1, 0x2A, 1, 0x2B);

}
