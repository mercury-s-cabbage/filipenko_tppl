#include <Arduino.h>
#define leftPin A5
void setup() {
    Serial.begin(9600);
 
}

void loop() {

  if(Serial.available()>0){
    int teststr = Serial.read();
  
    if (teststr==112){
    for (size_t i = 0; i < 100; i++)
    {
    
        int left = analogRead(leftPin);
  

        Serial.write(left);
       
    }
     }
    else{
        Serial.println("unknown command");
    }


  }
  }