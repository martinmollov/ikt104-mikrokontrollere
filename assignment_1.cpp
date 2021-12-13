#include <Arduino.h>

void setup()
{
pinMode(5, OUTPUT);

Serial.begin(9600);

while (!Serial);

Serial.println("Input 1 to Turn LED on and 0 to turn it off");
}

void loop() 
{

if (Serial.available())
{

int state = Serial.parseInt();

if (state == 1)
{
digitalWrite(5, HIGH);
Serial.println("Command completed, LED turned ON");
}

if (state == 0)
{
digitalWrite(5, LOW);
Serial.println("Command completed, LED turned OFF");
}

}

}