#include <Arduino.h>
#define led 8
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0) {
     String teststr = Serial.readString();
    teststr.trim();
    if (teststr==""){
        digitalWrite(led,HIGH);
    }
    if (teststr=="d"){
        digitalWrite(led,LOW);
    }

  }     
}