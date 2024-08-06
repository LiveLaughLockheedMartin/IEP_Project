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

//Range of oxygen level 

int OxygenList[5][2] = {{0, 200},  // Extreme low range
                        {201, 400}, // Low range
                        {401, 600}, // Warning range
                        {601, 800}, // Sufficient range
                        {801, 1024}}; // Normal
void CheckO2 (int O2level, int OxygenList[][2]);
void setup() 
{
// pin setup
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

  knobvalue=analogRead(knob_pin); //knobvalue will represent oxygen level
  int normalO2lvl=500;
  CheckO2(knobvalue, OxygenList); // calling CheckO2 function with arguements
  

}

void CheckO2 (int O2level, int OxygenList[][2]) //parameters
{
  analogWrite(LED_BLUE, O2level/4);
  int flag=0; //to keep track of validity
  int i;
  for (i=0;i<5;i++)//Start for loop to iterate over 2D array
  {
      if (O2level>=OxygenList[i][0] && O2level<=OxygenList[i][1] ) //Check O2 range
      {
       flag=1;
        if (i==0)
          {
            Serial.println(O2level);
            Serial.println("Very low oxygen");
            digitalWrite(LED_YELLOW,LOW);
            digitalWrite(LED_GREEN,LOW);
            digitalWrite(LED_RED,HIGH); //Emit RED
          }
        else if (i==1)
          {
            Serial.println(O2level);
            Serial.println("Low oxygen");
            digitalWrite(LED_GREEN,LOW); 
            digitalWrite(LED_YELLOW,LOW);
            digitalWrite(LED_RED,HIGH);  // Blink Red
            delay(1000);
            digitalWrite(LED_RED,LOW);
            delay(1000);
          }
        else if (i==2)
          {
            Serial.println(O2level);
            Serial.println("Warning");
            digitalWrite(LED_GREEN,LOW); 
            digitalWrite(LED_YELLOW,HIGH);// Blink Yellow
            delay(1000);
            digitalWrite(LED_YELLOW,LOW);
            delay(1000);
          }
        else if (i==3)
          {
            Serial.println(O2level);
            Serial.println("Sufficient");
            digitalWrite(LED_YELLOW,LOW);
            digitalWrite(LED_RED,LOW);
            digitalWrite(LED_GREEN,HIGH); // Blinking GREEN
            delay(1000);
            digitalWrite(LED_GREEN,LOW);
            delay(1000);
          }
        else if(i==4)
          {
            Serial.println(O2level);
            Serial.println("Normal level");
            digitalWrite(LED_YELLOW,LOW);
            digitalWrite(LED_RED,LOW);
            digitalWrite(LED_GREEN,HIGH); // Emit GREEN
          }
        break; // Break after conditions met
      }

  }
 if (flag == 0) {
      Serial.println("Invalid"); //Error handling
  }
}

    

