#include <Arduino.h>

#define leftPin A1

#define rightPin A0

void setup() {
  Serial.begin(9600);
  Serial.print("HELOO");

}

void loop() {
  int left = analogRead(leftPin);
  int right = analogRead(rightPin);

  Serial.print("left ");
  Serial.print(left);
  Serial.print(" right ");
  Serial.print(right);
  Serial.println("");
  delay(800);

}