const int step_pin = 13;
const int direction_pin = 12;
// 200 steps for 360 degree
const int STEPS_PER_TURN = 200;
// Adjust the delay for control speed
const int delay_between_step_microsec = 5000;
void setup() {
  Serial.begin(9600);
  pinMode(step_pin, OUTPUT);
  pinMode(direction_pin, OUTPUT);
}
void step(bool forward) {
  // setting the direction
  if (forward == true) {
    digitalWrite(direction_pin, HIGH);
  } else {
    digitalWrite(direction_pin, LOW);
  }
  // creating a step
  digitalWrite(step_pin, HIGH);
  // minimum delay is 1.9us
  digitalWrite(step_pin, LOW);
}
void steps(int number_of_steps) {
  bool move_forward = true;
  // Establishing the direction
  if (number_of_steps >= 0) {
    move_forward = true;
  } else {
    move_forward = false;
    number_of_steps = -number_of_steps;
  }
  // Generating the steps
  for (int i = 0; i < number_of_steps; i++) {
    step(move_forward);
    // Delay for proper speed
    delayMicroseconds(delay_between_step_microsec);
  }
}
void loop() {
  steps(50);
  delay(50);
  steps(-50);
  // delay(1000);
  // steps(-50);
  //your code here
}