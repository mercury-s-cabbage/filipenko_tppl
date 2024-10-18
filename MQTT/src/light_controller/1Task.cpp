#include <Arduino.h>
#define leftPin A5
void setup() {
    Serial.begin(9600);
 
}

void loop() {
  if(Serial.available()>0){
    int teststr = Serial.read();
  
    if (teststr==112){
     
    int left = analogRead(leftPin);
    byte leftByte = left / 4; 

    Serial.write(leftByte);
    }
    else{
        Serial.println("unknown command");
    }


  }
  }