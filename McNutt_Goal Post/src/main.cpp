#include <Arduino.h>
int led1 = 3;
int led2 = 4;
int led3 = 5;
int Trig = 7;
int Echo = 6;
long duration, cm;
long sendVal;
void setup() {
  Serial.begin(9600);
  Serial.println("This is the test run for the Goal Post V1");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
pinMode(Trig, OUTPUT);
pinMode(Echo, INPUT);
digitalWrite(led1, LOW);  
digitalWrite(led2, LOW);
digitalWrite(led3, LOW);


  }

void loop() {

   long duration, cm;
  // Getting a reading from the ultrasonic sensor
  // 1. produce a 5us HIGH pulse in Trig
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(Trig, LOW);

  // 2. measure the duration of the HIGH pulse in Echo
  //      & every 58 us is an obstacle distance of 1 cm
  duration = pulseIn(Echo, HIGH);
  cm = duration / 58;
  Serial.print(cm);
  Serial.println(F("cm"));

if (cm < 3)
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  delay(1000);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(1000);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
}

else {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

}