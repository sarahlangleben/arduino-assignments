#include <analogWrite.h>
const int IRSensor = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(IRSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogToMvolt = map(analogRead(IRSensor), 0, 4095, 0, 3300);
  int mvoltToVolt = float(analogToMvolt/100);
  int centimeter = float(70/mvoltToVolt-6)+15;
  int millimeter = centimeter*10;
  Serial.println(millimeter);
}
