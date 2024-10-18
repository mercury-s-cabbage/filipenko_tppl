#include <Arduino.h>
#define leftPin A5
void setup() {
    Serial.begin(9600);
 
}

void loop() {

    int left = analogRead(leftPin);
    byte leftByte = left / 4; 

    Serial.write(leftByte);

  }