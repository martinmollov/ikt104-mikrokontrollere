#include <Arduino.h>
#include <Arduino_MKRENV.h>

const int buttonPin = 5;     // the number of the pushbutton pin
const int ledPin =  A0;      // the number of the LED pin

float illuminance = 0;

void setup() 
{
  Serial.begin(9600);

  while (!Serial);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  } 
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);

}

void loop() 
{
  int buttonLast;
  int button = digitalRead(buttonPin);

  // Read illuminance
    for (int i=0; i <= 1000; i++)
    {
      illuminance = ENV.readIlluminance();
    
    }

// dimming the LED according to illiminance value read from the sensor
      if (illuminance > 200)
      {
        // set brightness level to 255 (full brightness, same as HIGH)
        analogWrite(ledPin, 255);
        
      } else if (illuminance < 200 && illuminance > 100)
        {
          // set brightness level to 150
          analogWrite(ledPin, 150);
          
        } else if (illuminance < 100 && illuminance > 50)
          {
            // set brightness level to 100
            analogWrite(ledPin, 100);
           
          } else if (illuminance < 50 && illuminance > 0)
            {
              // set brightness level to 0 (LED is OFF, same as LOW)
              analogWrite(ledPin, 0);
              
            }

  // If the button is pressed
  if (button && !buttonLast)
  {
  
      // print the sensor value
      Serial.print("Illuminance = ");
      Serial.print(illuminance);
      Serial.println(" lx");

      // print an empty line
      Serial.println();

      

            Serial.println();

      //delay(100);
    }

    
    //analogWrite(ledPin, 0);
  }
