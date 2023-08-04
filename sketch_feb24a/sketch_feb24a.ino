const int IRSensor = 13;
const int step_pin = 27;
const int direction_pin = 12;
// 200 steps for 360 degree
const int STEPS_PER_TURN = 200;
// Adjust the delay for control speed
const int delay_between_step_microsec = 5000;

const int sensor_pin = A3;
int position;        //track position
int reading;         //reading from sensor
int step_count = 0;  // count steps

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
  if (Serial.read() != 'N') {
    position = map(step_count % 50, 0, 50, 0, 160);  // angle in degrees
    if (step_count <= 88) {
      step(true);
      delay(50);
      step_count++;
      // position = map(step_count, 0, 90, 0, 160); // angle in degrees
      reading = int(70) / (analogRead(sensor_pin) / 1000.0) - 6.5;
    }
    if (step_count > 88) {
      step(false);
      delay(50);
      step_count++;
      // position = map(step_count%50, 0, 90, 0, 160); // angle in degrees
      reading = int(70) / (analogRead(sensor_pin) / 1000.0) - 6.5;
    }
  }
  if (step_count > 177) {
    step_count = 0;
  }
  Serial.print(position * 10);  // angle in 1/10 of degree
  Serial.print(",");
  Serial.print(abs(reading * 10));  // range in mm
  Serial.println(".");
}