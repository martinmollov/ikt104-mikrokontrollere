#include <Arduino.h>
#include <Wire.h>

void write(char reg) {
Wire.beginTransmission(0x5F);
Wire.write(reg);
Wire.endTransmission();
}

void write2(char reg, char value) {
Wire.beginTransmission(0x5F);
Wire.write(reg);
Wire.write(value);
Wire.endTransmission();
}

void request(int bytes) {
// Request 1 byte of data from this register
Wire.requestFrom(0x5F, bytes);
// Wait for the data to become available (do nothing in a while loop)
while (Wire.available() == 0);
}

void print(char var) {
// Serial.print("0x");
Serial.println(var, BIN);
delay(300);
}

void read_hum(char addr, int hum_l_byte, char hum_l_reg, int hum_h_byte, char hum_h_reg){

    // Set the register address on device 0x5F (HTS221 sensor) to 0x0F (WHO_AM_I register)
Wire.beginTransmission(addr);
Wire.write(hum_l_reg);
Wire.endTransmission();

// Request 1 byte of data from this register
Wire.requestFrom(addr, hum_l_byte);

// Wait for the data to become available (do nothing in a while loop)
while (Wire.available() == 0);

// Read data into a variable
byte hum_l = Wire.read();
Serial.print("Hum L: ");
Serial.println(hum_l, BIN);

Wire.beginTransmission(addr);
Wire.write(hum_h_reg);
Wire.endTransmission();

// Request 1 byte of data from this register
Wire.requestFrom(addr, hum_h_byte);

// Wait for the data to become available (do nothing in a while loop)
while (Wire.available() == 0);

// Read data into a variable
byte hum_h = Wire.read();
Serial.print("Hum H: ");
Serial.println(hum_h, BIN);


uint16_t humidity = hum_h << 8;
humidity |= hum_l;

Serial.print("Humidity: ");
Serial.println(humidity, BIN);
}

void read_temp(char addr, int temp_l_byte, char temp_l_reg, int temp_h_byte, char temp_h_reg){

    // Set the register address on device 0x5F (HTS221 sensor) to 0x0F (WHO_AM_I register)
Wire.beginTransmission(addr);
Wire.write(temp_l_reg);
Wire.endTransmission();

// Request 1 byte of data from this register
Wire.requestFrom(addr, temp_l_byte);

// Wait for the data to become available (do nothing in a while loop)
while (Wire.available() == 0);

// Read data into a variable
byte temp_l = Wire.read();
Serial.print("Temp L: ");
Serial.println(temp_l, BIN);

Wire.beginTransmission(addr);
Wire.write(temp_h_reg);
Wire.endTransmission();

// Request 1 byte of data from this register
Wire.requestFrom(addr, temp_h_byte);

// Wait for the data to become available (do nothing in a while loop)
while (Wire.available() == 0);

// Read data into a variable
byte temp_h = Wire.read();
Serial.print("Temp H: ");
Serial.println(temp_h, BIN);


uint16_t temperature = temp_h << 8;
temperature |= temp_l;

Serial.print("Temperature: ");
Serial.println(temperature, BIN);
}