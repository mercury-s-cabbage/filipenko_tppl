#include <Arduino.h>
//ports o
const int red_led=4;
const int green_led=2;
const int yellow_led=3;

//green, blinking, yellow, red, yellow
const long durations[] = {10000, 2000, 1000, 7000, 1000};
//time between LOW and HIGH during blinking
const int traffic_blink_delay=200;
//yellow lighting between modes
const int switch_yellow_delay=3000;

//??
const long traffic_delay=16000;
const  int traffic_yellow_delay=7000;

//mode 0 -default, 1 -manual
int mode=1;
int manual_max_time=60000;

//increment how to go array
int inc=1;
//light 0 -green, 1 -yellow, 2 -red
int ledNow=2;


//additional display
#define CLK 9
#define DIO 8
#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);

//pins
int myPins[] = {red_led, yellow_led, green_led};
void setup() 
{ 
  for (int pin:myPins)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }

  disp.clear();
  disp.brightness(7);
  Serial.begin(9600);
}

//blinking function
void endBlink(int led)
{
    int start_blinking=millis();
    int now_blinking=millis();

    int start_light=millis();
    digitalWrite(myPins[led],HIGH);
    bool is_lighting=true;
    while (now_blinking-start_blinking<=durations[1])
    {
      int now_light=millis();
      if(now_light-start_light>=traffic_blink_delay)
      {
        if (is_lighting)
        {
          digitalWrite(myPins[led],LOW);
          is_lighting=false;
          start_light=millis();
        }
        else
        {
          digitalWrite(myPins[led],HIGH);
          is_lighting=true;
          start_light=millis();
        }
      }
      now_blinking=millis();
    }
    digitalWrite(myPins[led],LOW);
}

void switchYellow()
{
    int start_yellow=millis();
    int now_yellow=millis();
    digitalWrite(yellow_led,HIGH);
    while (now_yellow-start_yellow<switch_yellow_delay)
    {
      now_yellow=millis();
    }
    digitalWrite(yellow_led,LOW);
}

//потом перенести в энтер мод
int manual_start_time=millis();
void loop()
{
    //enter mode
    //...

    //manual
    if (mode==1)
    { 
      for (int pin:myPins)
      {
          digitalWrite(pin, LOW);
      }
      int manual_now_time=millis();
      while(manual_now_time-manual_start_time<manual_max_time)
      {
        //enter commands
        //...
        manual_now_time=millis();
      }
      switchYellow();
      mode=0;
    }

    if (mode == 0) {
        for (int pin:myPins){
                digitalWrite(pin, LOW);}
        long start_time=millis();
        bool fl=true;
        bool switchTurn=false;
       // int pinNow=0;
        while (fl)
        {   disp.display(0,ledNow);
            if (Serial.available() > 0)
          {   
              String input=Serial.readString();
              if (input.indexOf("stop")!=-1){
                endBlink(ledNow);
                disp.display(1,1);
                mode=1;
                break;



              }  
          }

        if (millis()>=start_time+traffic_delay && ledNow!=1) 
        {   start_time=millis();
            endBlink(ledNow);
            disp.display(2,1);

            ledNow=ledNow+inc;
            if (ledNow==3){
                ledNow=1;
                inc=-1;
            }
            if (ledNow==-1){
                ledNow=1;
                inc=1;
            }
        } else {
            disp.display(0,ledNow);
            digitalWrite(myPins[ledNow],HIGH);
        }
        if (start_time+traffic_yellow_delay<=millis() and ledNow==1){
            start_time=millis();
            disp.display(2,0);
            digitalWrite(myPins[ledNow],LOW);
            ledNow+=inc;
        } else {
            digitalWrite(myPins[ledNow],HIGH);
        }
        disp.display(3,inc+3);
        //disp.clear();
        }
    }
}