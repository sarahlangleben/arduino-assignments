#include <analogWrite.h>
// LED Pin
const int ledPin = 13;
void setup() {
  pinMode(ledPin, OUTPUT);
}
void loop() {
  // fade the LED on thisPin from off to brightest:
  for (int brightness = 0; brightness < 255; brightness++) {
    analogWrite(ledPin, brightness);
    delay(5);
  }
  // fade the LED on thisPin from brithstest to off:
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(5);
  }
}