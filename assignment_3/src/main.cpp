#include<Arduino.h>
#include<Wire.h>

// HTS221 I2C address is 0x5F
#define Addr 0x5F
int LEDgreen = A0;
int LEDred = A1;

void setup() 
{
  // Initialise I2C communication as MASTER 
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select average configuration register
  Wire.write(0x10);
  // Temperature average samples = 256, Humidity average samples = 512
  Wire.write(0x1B);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register1
  Wire.write(0x20);
  // Power ON, Continuous update, Data output rate = 1 Hz
  Wire.write(0x85);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop() 
{
  unsigned int data[2];
  unsigned int val[4];
  unsigned int H0, H1, H2, H3, T0, T1, T2, T3, raw;

  // Humidity calliberation values
  for(int i = 0; i < 2; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Send data register
    Wire.write((48 + i));
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 1 byte of data
    Wire.requestFrom(Addr, 1);
    
    // Read 1 byte of data
    if(Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }
  
  // Convert Humidity data
  H0 = data[0] / 2;
  H1 = data[1] / 2;
  
  for(int i = 0; i < 2; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Send data register
    Wire.write((54 + i));
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 1 byte of data
    Wire.requestFrom(Addr,1);
    
    // Read 1 byte of data
    if(Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }
  // Convert Humidity data
  H2 = (data[1] * 256.0) + data[0];
  
  for(int i = 0; i < 2; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Send data register
    Wire.write((58 + i));
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 1 byte of data
    Wire.requestFrom(Addr,1);
    
    // Read 1 byte of data
    if(Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }
  // Convert Humidity data
  H3 = (data[1] * 256.0) + data[0];

  // Temperature calliberation values
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Send data register
  Wire.write(0x32);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr,1);

  // Read 1 byte of data
  if(Wire.available() == 1)
  {
    T0 = Wire.read();
  }

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Send data register
  Wire.write(0x33);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr,1);

  // Read 1 byte of data
  if(Wire.available() == 1)
  {
    T1 = Wire.read();
  }
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Send data register
  Wire.write(0x35);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);

  // Read 1 byte of data
  if(Wire.available() == 1)
  {
    raw = Wire.read();
  }

  raw = raw & 0x0F;
  
  // Convert the temperature calliberation values to 10-bits
  T0 = ((raw & 0x03) * 256) + T0;
  T1 = ((raw & 0x0C) * 64) + T1;

  for(int i = 0; i < 2; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Send data register
    Wire.write((60 + i));
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 1 byte of data
    Wire.requestFrom(Addr,1);
    
    // Read 1 byte of data
    if(Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }
  // Convert the data
  T2 = (data[1] * 256.0) + data[0];
    
  for(int i = 0; i < 2; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Send data register
    Wire.write((62 + i));
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 1 byte of data
    Wire.requestFrom(Addr,1);
    
    // Read 1 byte of data
    if(Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }
  // Convert the data
  T3 = (data[1] * 256.0) + data[0];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Send data register
  Wire.write(0x28 | 0x80);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 4 bytes of data
  Wire.requestFrom(Addr,4);
  
  // Read 4 bytes of data
  // humidity msb, humidity lsb, temp msb, temp lsb
  if(Wire.available() == 4)
  {
    val[0] = Wire.read();
    val[1] = Wire.read();
    val[2] = Wire.read();
    val[3] = Wire.read();
  }
  
  // Convert the data
  float humidity = (val[1] * 256.0) + val[0];
  humidity = ((1.0 * H1) - (1.0 * H0)) * (1.0 * humidity - 1.0 * H2) / (1.0 * H3 - 1.0 * H2) + (1.0 * H0);
  int temp = (val[3] * 256) + val[2];
  float cTemp = (((T1 - T0) / 8.0) * temp) / T3 + (T0 / 8.0);

  // Output data to serial monitor
  Serial.print("\nRelative humidity : ");
  Serial.print(humidity);
  Serial.println(" % RH");
  Serial.print("Temperature in Celsius : ");
  Serial.print(cTemp);
  Serial.println(" C");

  if (cTemp >= 28.00)
  {
      analogWrite(LEDgreen, 0);
  }else{
    analogWrite(LEDgreen, 255);
  }

  if (humidity >= 50.00)
  {
      analogWrite(LEDred, 0);
  }else{
    analogWrite(LEDred, 255);
  }

  delay(500);
}
