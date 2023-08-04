#include <analogWrite.h>
// Motor control
const int motorEnablePin = 13;
const int leftSidePin = 12;
const int rightSidePin = 27;
const int encoderPin = 26;   // Pin A0
const int motorSpeed = 200;  // Speed of motor (0-
const int sensorPin = A0;
// old state of the encoder
boolean old_state = false;
// current state of the encoder
boolean current_state = false;
// current transition count
boolean direction; //false = forward, true = backward
int pulse_count;
// number of transition for a full turn
const int full_turn_count = 60;
void setup() {
  // configure the motor pins
  pinMode(motorEnablePin, OUTPUT);
  pinMode(leftSidePin, OUTPUT);
  pinMode(rightSidePin, OUTPUT);
  // Motor is off going forward
  analogWrite(motorEnablePin, 0);
  // digitalWrite(leftSidePin, HIGH);
  // digitalWrite(rightSidePin, LOW);
  // configure the photo-transistor pin
  pinMode(encoderPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  // reset the pulse counter
  pulse_count = 0;
  forward();
  // start the motor at 60% speed
  analogWrite(motorEnablePin, 153);
  // loop until we get the correct count
  while (pulse_count < full_turn_count) {
    // read the state of the photo-transistor
    current_state = digitalRead(encoderPin);
    //Serial.println(current_state);
    if (current_state != old_state) {
      // we detected a transition
      pulse_count++;
    }
    if(pulse_count > 30){
      analogWrite(motorEnablePin, 0);
      delay(5000);
    }
    old_state = current_state;
  }
}

void forward(){
  direction = false;
  digitalWrite(leftSidePin, HIGH);
  digitalWrite(rightSidePin, LOW);
}
void backward(){
  direction = true;
  digitalWrite(leftSidePin, LOW);
  digitalWrite(rightSidePin, HIGH);
}

  // while(pulse_count < 30){
  //   if(direction == false){
  //     backward();
  //   }
  //   if(direction == true){
  //     forward();
  //   }
  // }
  // if(pulse_count >= 30){
  //   if(direction == false){ //forward
  //     direction = true;
  //     pulse_count = 0;
  //   }
  //   if(direction == true){
  //     direction = false;
  //     pulse_count = 0;
  //   }
  //}
  // switch off the motor
  // wait a bit
  // backward();
  // delay(1000);