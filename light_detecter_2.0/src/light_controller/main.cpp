#include <Arduino.h>
int myFunction(int, int);
#define leftPin A5
void setup() {
    Serial.begin(9600);
 
}

void loop() {
  int left = analogRead(leftPin);
  Serial.println(left);
}