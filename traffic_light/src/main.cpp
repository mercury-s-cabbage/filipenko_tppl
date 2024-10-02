#include <Arduino.h>
const int red_led=4;
const int green_led=2;
const int blue_led=3;
const long traffic_delay=16000;
const int traffic_blink_count=3;
const int traffic_blink_delay=600;
const  int traffic_yellow_delay=7000;
int mode=0;
int inc=1;
int ledNow=2;
//mode 0  -default 
//mode 1  -service


#define CLK 9
#define DIO 8
#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);
int myPins[] = {red_led, blue_led, green_led};
void setup() {
  
  // put your setup code here, to run once:
  for (int pin:myPins){
 pinMode(pin, OUTPUT);
 digitalWrite(pin, HIGH);
  }
  delay(120);
    for (int pin:myPins){
  digitalWrite(pin, LOW);
  delay(120);
  }
  disp.clear();
  disp.brightness(7);
Serial.begin(9600);

}

void endBlink(int led)
{
     for (size_t i = 0; i < traffic_blink_count; i++)
                {
               
                digitalWrite(myPins[led],HIGH);
                delay(traffic_blink_delay);
                digitalWrite(myPins[led],LOW);
                delay(traffic_blink_delay);      
                }


}

bool service_menu=true;
void loop(){
   
    if (mode==1)
    { int start_time=millis();
      bool switched=true;
      int pinNow=1; 
      long time_to_end=60000; 
      long start_time_to_end=millis();
        while (fl){
        if (start_time_to_end+time_to_end<=millis){
            mode=0;
            break;
        }
        if (service_menu){
            if (start_time+traffic_blink_delay<=millis()){
            start_time=millis();

            switched=!switched;
        } else {
            if (switched){
                digitalWrite(myPins[1],HIGH);
                disp.display(2,9);
            } else {
                 digitalWrite(myPins[1],LOW);
                 disp.display(2,0);
            }
    
        }

         String str="";
                if (Serial.available() > 0) 
                {     
                str = Serial.readString();
                if (str.indexOf("red")!=-1) {
                       
                       endBlink(pinNow);
                       
                       digitalWrite(red_led,LOW);
                       pinNow=0;
                       
                }


                }






        } 






        }


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
                service_menu=true;
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