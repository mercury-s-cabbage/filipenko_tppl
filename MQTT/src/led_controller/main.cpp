#include <Arduino.h>
#define led 4
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0) {
     int teststr = Serial.read();
    if (teststr==117){//u
        digitalWrite(led,HIGH);
    }
    if (teststr==100){//d
        digitalWrite(led,LOW);
    }
    Serial.println(teststr);
  }     
}