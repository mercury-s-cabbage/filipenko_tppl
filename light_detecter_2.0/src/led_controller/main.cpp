#include <Arduino.h>
#define led 8
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0) {
     String teststr = Serial.readString();
    teststr.trim();
    if (teststr=="on"){
        digitalWrite(led,HIGH);
    }
    if (teststr=="off"){
        digitalWrite(led,LOW);
    }

  }     
}