#include <analogWrite.h>
const int potPin = A3;
// const int buzzerPin = 33; 
const int redPin = 33;
const int greenPin = 27; 
const int bluePin = 12;
const int IRSensor = 13;
int potVal = 0;
int sensorVal = 0;


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
  analogWrite(buzzerPin, 100); //control speaker
  sensorVal = analogRead(IRSensor);
  // Serial.println(sensorVal);
  sensorVal = map(sensorVal, 1000, 3000, 0, 4); //1000: too close, 1800s and less: too far, 2900+: good
  //converted: the lower the number, the closer you are. -1 is too far. 
  Serial.println(sensorVal);
  potVal = analogRead(potPin);
  potVal = map(potVal, 0, 4095, 1, 4); //meh good enough
  //the highest distance this works for is ~14 cm, otherwise you can't tell how far it is 
  Serial.println(potVal);
  delay(1000);
  int val = distCheck(sensorVal, potVal);
  int brightness = getDiff(sensorVal, potVal);
  switch(val) {
    case 0:
      turnOffLight();
      break;
    case 1:
      turnOffLight();
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      break;
    case -1:
      turnOffLight();
      digitalWrite(redPin, HIGH);
      break;
  }
    // case 1: 
      // digitalWrite(redPin, 100);
      // digitalWrite(greenPin, 20);
  // if(distCheck(sensorVal, potVal) == -1){
    //   Serial.println("too far");
    //   digitalWrite(redPin, HIGH);
    // }
    // if(distCheck(sensorVal, potVal) == 1){
    //   Serial.println("too close");
    //   digitalWrite(redPin, 100);
    //   digitalWrite(greenPin, 20);
    // }
    // analogWrite(LED_BUILTIN, 0);
    // analogWrite(redPin, HIGH); //no idea why this is so dim, but this is light control syntax
    // int sensorVal = digitalRead(IRSensor); 
    // Serial.println(analogRead(IRSensor));
    // delay(1000);
    // Serial.println(LED_BUILTIN);
    // Serial.println(sensorVal);
}

void turnOffLight(){
  digitalWrite(redPin, 0);
  digitalWrite(greenPin, 0);
}
int distCheck(int current, int target){ //-1 = too far, 0 = perfect, 1= too close
  if(current == target){
    return 0;
  }
  else if(current > target or current == -1){ //-1 is case for 4
    return -1;
  }
  else if(current < target){
    return 1;
  }
}
int getDiff(int current, int target){
  Serial.println(abs(target-current)*63);
  return abs(target-current)*63;
}
// int convertVolt(int reading){
//   map(reading, 0, 4095, 0, 4);
// }
//SPEC:
// too far: LED turns red
// too close: LED turns yellow
// to determine what is "too close" or "too far", use the pentiometer to set the 
// distance. 


//2.17 changes:
// potentiometer and sensor need to be operating in centimeters, formulas are on the slides
// the light will get dimmer the closer you get. 


//1: get the data from distance sensor X
//    convert data with map X
//2: set a limit determined by potentiometer
    //convert data with map X
//pento --> distance X
  //3.1: store data from pentometer reading. After 1s of no change store the data. X (honestly don't need the timing aspect)
  //3.2: if(sensorVal == potVal){turn light on, buzzer sounds} 
  //3.3: if(sensorVal > potVal){ too close?}
  //3.4 if(sensorVal < potVal){ too far?}
//3: LED lights up based on pentmeter + sensor data 
//4. speaker plays at target distance