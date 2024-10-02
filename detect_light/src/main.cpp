#include <Arduino.h>

#define leftPin A5
#define rightPin A0
#define leftLed 6
#define serviceLed 7
#define rightLed 8


void setup() {
   pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  pinMode(serviceLed, OUTPUT);
  Serial.begin(9600);
  Serial.println("calibrate..");

  // Устанавливаем пины в режим выхода
 
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