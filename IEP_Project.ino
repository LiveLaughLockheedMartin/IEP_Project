#define LDR_pin A2
#define LED_RED 4 
#define LED_GREEN 5 
#define LED_BLUE 6 
#define LED_YELLOW 7
#define Button1 8
#define Button2 9
#define Buzzerpin 3
#include "RichShieldPassiveBuzzer.h"
#define knob_pin A0
#include <Wire.h>
#include "RichShieldTM1637.h"
#define CLK_pin 10
#define DIO_pin 11
TM1637 disp(CLK_pin,DIO_pin);
int knobvalue;
int LDR;


void setup() 
{

pinMode(LED_RED, OUTPUT);
pinMode(LED_GREEN,OUTPUT);
pinMode(LED_BLUE,OUTPUT);
pinMode(LED_YELLOW,OUTPUT);
pinMode(Button1,INPUT_PULLUP);
pinMode(Button2,INPUT_PULLUP);
Serial.begin(9600);
  
  
disp.init();
}

void loop() 
{
  knobvalue=analogRead(knob_pin);

}
