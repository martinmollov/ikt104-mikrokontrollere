#include <samd21/include/samd21g18a.h>
#include <samd21/include/pio/samd21g18a.h>

#include <Arduino.h>

#include <DFRobot_RGBLCD.h>

int r,g,b;
int t=0;

DFRobot_RGBLCD lcd(16,2);  //16 characters and 2 lines of show

int counter = 0;

void display ();

// Create a pointer to Port A DIR register (base + 0x00)
uint32_t* PORTA_DIR_P = (uint32_t*)0x41004400 + 0x00;
#define PORTA_DIR (*(uint32_t*)(0x41004400 + 0x00))

// Create a pointer to Port A DIR register (base + 0x10)
uint32_t* PORTA_OUT_P = (uint32_t*)0x41004400 + 0x10;
#define PORTA_OUT (*(uint32_t*)(0x41004400 + 0x10))

void setup()
{
 Serial.begin(9600);

 // Use the dereference operator to access the register value.
// |= will set the bits given on the right side of the express.
*PORTA_DIR_P |= (1 << 20);

 // initialize LCD display
  lcd.init();

 while (!Serial);

 // Set port A pin 21 to input (0 is input, 1 is output)
 PORT->Group[0].DIR.reg &= ~PORT_PA10;

 // Set input to pullup
 PORT->Group[0].OUT.reg |= PORT_PA10;

 // Enable the pullup
 PORT->Group[0].PINCFG[PIN_PA10].reg |= PORT_PINCFG_PULLEN;

 // Set port A pin 20 to input (0 is input, 1 is output)
 PORT->Group[0].DIR.reg &= ~PORT_PA11;

 // Set input to pullup
 PORT->Group[0].OUT.reg |= PORT_PA11;

 // Enable the pullup
 PORT->Group[0].PINCFG[PIN_PA11].reg |= PORT_PINCFG_PULLEN;
}

void loop()
{
 // Check if the relevant bit is 1. If it is 1 the button is not pressed
 if (!(PORT->Group[0].IN.reg & PORT_PA10))
   delay(1);
 else
 {
   //Serial.println("Button is pressed (pin PA10)");
   counter ++;
   lcd.clear();
   // Turn the LED on
   PORTA_OUT |= (1 << 20);
   delay(100);
   // Turn the LED off
   PORTA_OUT &= ~(1 << 20);
   //Serial.println("Counter increased by 1");
 }

 // Check if the relevant bit is 1. If it is 1 the button is not pressed
 if (!(PORT->Group[0].IN.reg & PORT_PA11))
   delay(1);
 else
 {
   //Serial.println("Button is pressed (pin PA11)");
   counter --;
   lcd.clear();
   // Turn the LED on
   PORTA_OUT |= (1 << 20);
   delay(100);
   // Turn the LED off
   PORTA_OUT &= ~(1 << 20);
   //Serial.println("Counter decreased by 1");
 }

 //Serial.print("Counter: ");
 //Serial.println(counter);
 display();

 //delay(100);
}

void display ()
{
  r= (abs(sin(3.14*t/180)))*255;          //get R,G,B value
  g= (abs(sin(3.14*(t+60)/180)))*255;
  b= (abs(sin(3.14*(t+120)/180)))*255;
  t=t+3;
  lcd.setRGB(r, g, b);                  //Set R,G,B Value
  lcd.setCursor(0,0);
  lcd.print("Counter: ");
  //lcd.setCursor(0,11);
  lcd.print(counter);
  //R:0-255 G:0-255 B:0-255

  delay(1);
}
