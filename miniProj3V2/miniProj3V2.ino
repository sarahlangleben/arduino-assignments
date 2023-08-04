#include <analogWrite.h>
const int potPin = A3;
const int buzzerPin = 14; 
const int redPin = 33;
const int greenPin = 27; 
const int bluePin = 12;
const int IRSensor = 13; 

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(IRSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //convert analog to voltage for sensor
  int analogToMvolt = map(analogRead(IRSensor), 0, 4095, 0, 3300);
  //convert mV to V
  int mvoltToVolt = float(analogToMvolt/100);
  //convert V to cm-- add 15 at the end bc we're working at 15 cm + 
  int distance = float(70/mvoltToVolt-6)+15; 
  //sensor readings: distance increase = lower voltage. 
  int potMvolt = map(analogRead(potPin), 0, 4095, 0, 3300);
  int potMvoltToVolt = float(potMvolt/100);
  int target_distance = float(70/potMvoltToVolt-6)+15;
  delay(1000);
  Serial.print("current distance: ");
  Serial.print(distance); Serial.println(" cm, ");
  Serial.print("target distance: "); Serial.print(target_distance); Serial.println(" cm ");
  // Serial.println(target_distance);
  if(distance == target_distance){
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(buzzerPin, 100);
    delay(1000);
    analogWrite(buzzerPin, 0);
  }
  if(distance < target_distance){
    analogWrite(redPin, map(abs(potMvolt-analogToMvolt), 0, 4095, 0, 255));
    analogWrite(greenPin, 0);
  }
  if(distance > target_distance){
    analogWrite(redPin, map(abs(potMvolt-analogToMvolt), 0, 4095, 0, 255));
    analogWrite(greenPin, map(abs(potMvolt-analogToMvolt), 0, 4095, 0, 255));
  }
}