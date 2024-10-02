#include <Arduino.h>

#define leftPin A5
#define rightPin A0
#define leftLed 6
#define serviceLed 7
#define rightLed 8
// минимум максимум для датчиков

// 0 - maxLeft 1 - minLeft 2 - maxRight 3 - minRight массив для хранения калибровок датчиков
int values[] = {0, 0, 0,0}; 
// время на калибровку
int delayForCalibrate=5000;
// время на смену позиции с светлого на черное
int delayForSwithPos=1200;
void setup() {
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  pinMode(serviceLed, OUTPUT);
  digitalWrite(serviceLed,HIGH);
  //delay(delayForSwithPos);
  // change delay to millis
  long start=millis();
  while (start+delayForSwithPos>=millis()){
  }
  // 
  Serial.begin(9600);
 

  //переменные для цикла переключают  датчики  и светодиоды в цикле
  int ledNow=leftLed;
  int pinNow=leftPin;

  // цикл калибровки
  for (size_t i = 0; i < 4; i++)
  {
    //break;
    //ждем смену состояния 
    digitalWrite(serviceLed,LOW);
//    delay(delayForSwithPos);
       // change delay to millis
      long start=millis();
      while (start+delayForSwithPos>=millis()){
      }

    digitalWrite(serviceLed,HIGH);
    //переключаем пины
    if (i==2){
      ledNow=rightLed;
      pinNow=rightPin;
    }
  // переключаем состояние с светолого на темное
  if (i==1 or i ==3){
    digitalWrite(ledNow,LOW);
  }else {
    digitalWrite(ledNow,HIGH);
  }
  //для подсчета среднего значения
  long count=0;
  long sum=0;
  long startCalibrate=millis();
  //цикл на калибровку одного состояния
  while (startCalibrate+delayForCalibrate>=millis()){
  
   sum+= analogRead(pinNow);
    count+=1;
  }
  //считаем среднее
  values[i]=sum/count;
  //Serial.println(values[i]);
  digitalWrite(ledNow,LOW);

}
//выводим
Serial.print("values");
for (size_t i = 0; i < 4; i++)
{
  Serial.print(values[i]);
  Serial.print("  ");
  Serial.println();

}
  digitalWrite(serviceLed,LOW);
}

void blinking(int led_l, int led_h)
{
  int start_time = millis();
  while(millis()-start_time<500)
  {
   digitalWrite(led_l,LOW);
   digitalWrite(led_h,HIGH);
  }
  start_time = millis();
  while(millis()-start_time<500)
  {
   digitalWrite(led_h,LOW);
  }
}
long time_start=millis();
int blinkInterval=500;
bool is_on=false;
int ledNow=0;
void loop() {
  //int values[] = {450, 60, 615, 30}; 
  float left = analogRead(leftPin);
  float right = analogRead(rightPin);

  float left_p = left/(values[0] - values[1])*100;
  float right_p = right/(values[2] - values[3])*100;


  if (left_p - right_p > 15.0)
  {
    digitalWrite(rightLed,LOW);
    ledNow=leftLed;
    //digitalWrite(leftLed,HIGH);
  }
  else if (left_p - right_p < -15.0)
  {
 
    digitalWrite(leftLed,LOW);
    ledNow=rightLed;
   // digitalWrite(rightLed,HIGH);
  }
  else if ((left_p>50.0) && (right_p>50.0))
  {
    digitalWrite(leftLed,HIGH);
    digitalWrite(rightLed,HIGH);
    ledNow = 0;
  }
  //blink 
  if (time_start+blinkInterval<=millis()){
    time_start=millis();
    if (is_on){
    digitalWrite(ledNow,HIGH);
      
    }else{
 digitalWrite(ledNow,LOW);
   
  Serial.print("left ");
  Serial.print(left_p);
  Serial.print("% right ");
  Serial.print(right_p);
  Serial.println("%");

  Serial.println(left_p - right_p);
    }
    is_on=!is_on;
  }
}