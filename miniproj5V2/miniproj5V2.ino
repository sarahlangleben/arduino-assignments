#include <analogWrite.h>
// Motor control
const int motorEnablePin = 13;
const int leftSidePin = 12;
const int rightSidePin = 27;
const int encoderPin = 26;  // Pin A0
// old state of the encoder
boolean old_state = false;
// current state of the encoder
boolean current_state = false;
// current transition count
boolean current_direction = false; //false = forward
boolean previous_direction = false; //true = backward
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
  digitalWrite(leftSidePin, HIGH);
  digitalWrite(rightSidePin, LOW);
  // configure the photo-transistor pin
  pinMode(encoderPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  // reset the pulse counter
  pulse_count = 0;
  // if(pulse_count == 120){
  //   pulse_count = 0;
  // }
  // start the motor at 60% speed
  // loop until we get the correct count
  while (pulse_count < 120) {
    // read the state of the photo-transistor
    current_state = digitalRead(encoderPin);
    Serial.println(current_state);
    if (current_state != old_state) {
      // we detected a transition
      pulse_count++;
    }
    old_state = current_state;
    if(pulse_count < 60){
      digitalWrite(leftSidePin, LOW);
      digitalWrite(rightSidePin, HIGH);
      analogWrite(motorEnablePin, 153);
    }
    // if(pulse_count < 60 && pulse_count > 60){
    //   analogWrite(motorEnablePin, 0);
    // }
    if(pulse_count == 60 || pulse_count == 0){
      analogWrite(motorEnablePin, 0);
      delay(5000);
    }
    if(pulse_count > 60){
      analogWrite(motorEnablePin, 153);
      digitalWrite(leftSidePin, HIGH);
      digitalWrite(rightSidePin, LOW);
      analogWrite(motorEnablePin, 153);
    }
  }
}
// void func(){
//   digitalWrite(leftSidePin, LOW);
//   digitalWrite(rightSidePin, LOW);
//   delay(1000);
// }

