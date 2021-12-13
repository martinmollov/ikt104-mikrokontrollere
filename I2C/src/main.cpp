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
//write2(0x28, 0xFF);
// Request 2 bytes of data
//request(2);
// Read 2 bytes of data
// humidity msb, humidity lsb.
//Serial.print("bytes received: ");
//Serial.println(Wire.available());
/*if(Wire.available() >= 2)
{
humidity = Wire.read(); // receive high byte (overwrites previous reading)
humidity = humidity << 8; // shift high byte to be high 8 bits
humidity |= Wire.read(); // receive low byte as lower 8 bits
Serial.print("Humidity: ");
Serial.println(humidity);
}
Serial.print("bytes remaining: ");
Serial.println(Wire.available());
//Point to TEMP_OUT_L and TEMP_OUT_H.
write(0x2A);
// Request 2 bytes of data
request(2);
// Read two bytes of data.
// temp msb, temp lsb
Serial.print("bytes received: ");
Serial.println(Wire.available());
if(Wire.available() >= 2)
{
temperature = Wire.read(); // receive high byte (overwrites previous reading)
temperature = temperature << 8; // shift high byte to be high 8 bits
temperature |= Wire.read(); // receive low byte as lower 8 bits
Serial.print("Temperature: ");
Serial.println(temperature);
}

Serial.print("bytes remaining: ");
Serial.println(Wire.available());*/
}