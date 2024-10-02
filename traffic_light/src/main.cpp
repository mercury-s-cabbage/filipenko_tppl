#include <Arduino.h>
//ports 
const int red_led=4;
const int green_led=2;
const int yellow_led=3;

//green, blinking, yellow, red, yellow
const long durations[] = {10000, 2000, 1000, 7000, 1000};
//time between LOW and HIGH during blinking
const int traffic_blink_delay=200;
//yellow lighting between modes
const int switch_yellow_delay=3000;

//mode 1 -default, 0 -manual
int mode=1;
long manual_max_time=60000;

//increment how to go array
int inc=1;
//light 0 -green, 1 -blinking, 2 -yellow, 3-red, 4-yellow
int ledNow=2;

//pins
int myPins[] = {green_led, green_led, yellow_led, red_led, yellow_led};
void setup() 
{ 
  for (int pin:myPins)
  {
    pinMode(pin, OUTPUT);
  }
  Serial.write(" Type 0 for manual, 1 for default \n");
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
    digitalWrite(red_led,LOW);
    digitalWrite(green_led,LOW);
    while (now_yellow-start_yellow<switch_yellow_delay)
    {
      now_yellow=millis();
    }
    digitalWrite(yellow_led,LOW);
}

int manual_start_time;
int default_start_time;
void loop()
{
    String buf = "";
    if (Serial.available() > 0) 
    {
      buf = Serial.readString();
      Serial.write("echo ");
      Serial.println(buf);
      if (buf == "0") //manual
      {
        if (String(mode)!=buf)
        {
          switchYellow();
          int manual_start_time=millis();
          Serial.write(" Changing mode to manual \n");
          Serial.write(" Type r for red, g for green \n");
        }
        mode = 0;
      }
      else if (buf == "1") //default
      {
        if (String(mode)!=buf)
        {
          switchYellow();
          int default_start_time=millis();
          Serial.write(" Changing mode to default\n");
        }
        mode = 1;
      }
    }

    //manual
    if (mode==0)
    { 
      int manual_now_time=millis();
      if(manual_now_time-manual_start_time<=manual_max_time)
      {
          if (buf == "g") 
          {
            Serial.write(" Green \n");
            digitalWrite(myPins[ledNow], LOW);
            ledNow=0;
            digitalWrite(myPins[ledNow], HIGH);
          }
          if (buf == "r")
          {
            Serial.write(" Red \n");
            digitalWrite(myPins[ledNow], LOW);
            ledNow=3;
            digitalWrite(myPins[ledNow], HIGH);
          }
      }
      else
      {
        Serial.write(" Time goes up \n");
        mode=1;
      }
    }
    //default
    if (mode == 1) 
    {

      //if blinking green
      if(ledNow==1)
      {
          endBlink(ledNow);
          ledNow += 1;
          default_start_time=millis();
      }
      else
      {
        int default_now_time=millis();
        digitalWrite(myPins[ledNow], HIGH);
        if (default_now_time-default_start_time>durations[ledNow])
        {
            digitalWrite(myPins[ledNow], LOW);
            ledNow += 1;
            if (ledNow>4)
            {
              ledNow=0;
            }
            default_start_time=millis();
        }
      }
    }
}