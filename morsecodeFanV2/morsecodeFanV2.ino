#include <string>
#include <analogWrite.h>
int buttonState = 0;
int lastButtonState = 0;
int startPressed = 0;
int endPressed = 0;
int holdTime = 0;
int idleTime = 0;
int count = 0;
const int buttonPin = 21;
const int ledPin = 13; 

String morse_code[6] = {""};
void setup() {
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}
void loop() {
  buttonState = digitalRead(buttonPin);
  if(buttonState != lastButtonState){
    updateState();
  }
  lastButtonState = buttonState;
}

void updateState(){
  if(count == 5){
    //Serial.println(morse_code[1]+","+morse_code[2]+","+morse_code[3]+","+morse_code[4]+","+morse_code[5]+","+morse_code[6]);
    translate(morse_code);
    count = 0;
    morse_code[6] = {""};
  }
  if(buttonState == LOW){
    startPressed = millis();
    idleTime = startPressed - endPressed;
    if(idleTime >= 10000){
      Serial.println("Resetting message");
      count = 0;
      morse_code[6] = {""};
    }
  }
  else {
    endPressed = millis();
    holdTime = endPressed - startPressed;
    if(holdTime >= 500 && holdTime < 1000){
      count++;
      Serial.println(count);
      Serial.println("dot ");
      morse_code[count] = "dot";
    }
    if(holdTime >= 1000){
      count++;
      Serial.println(count);
      Serial.println("dash ");
      morse_code[count] = "dash";
    }
  }
}

void translate(String arr[]){
  int dotCount = 0;
  int dashCount = 0;
  if(arr[1].equals("dash") && arr[5].equals("dot")){
    for(int i=0; i < 6; i++){
      if(arr[i].equals("dot")){
        dotCount++;
      }
    }
  }
  switch(dotCount){
    case 4:
      Serial.println("The message is six");
      motorMove(ledPin, 0.66*255);
      break;
    case 3:
      Serial.println("The message is seven");
      motorMove(ledPin, 0.77*255);
      break;
    case 2:
      Serial.println("The message is eight");
      motorMove(ledPin, 0.88*255);
      break;
    case 1:
      Serial.println("The message is nine");
      motorMove(ledPin, 0.99*255);
      break;
  }
  if(arr[1].equals("dot") && arr[5].equals("dash")){
    for(int i=0; i < 6; i++){
      if(arr[i].equals("dash")){
        dashCount++;
      }
    }
  }
  switch(dashCount){
    case 1: //4
      Serial.println("The message is four");
      motorMove(ledPin, 0.44*255);
      break; 
    case 2: //3
      Serial.println("The message is three");
      motorMove(ledPin, 0.33*255);
      break;
    case 3: //2
      Serial.println("The message is two");
      motorMove(ledPin, 0.22*255);
      break;
    case 4: //1
      Serial.println("The message is one");
      motorMove(ledPin, 0.11*255);
      break;
  }
  if(arr[1].equals("dot") && arr[5].equals("dot")){ //edge case: 5
    Serial.println("The message is five");
    motorMove(ledPin, 0.55*255);
  }
  if(arr[1].equals("dash") && arr[5].equals("dash")){ //edge case: 0
    Serial.println("The message is zero");
    motorMove(ledPin, 0);
  }
}

void motorMove(int ledPin, int speed){
  //Serial.println("motorMove called");
  analogWrite(ledPin, speed);
}


//1. get a count of button presses X
//2. time how long a button is pressed X
//3. differentiate between the two: how long is a dash, how long a dot? X
//4. translate the individual presses X
  //4.1 count how many presses-- max is five, once you hit five you can change motor speed X
  //4.3 after five presses, call individual motor control methods and reset count = 0. X
  //4.4 track idle time-- if over 10 seconds no press resent counter X
  //4.5 figuring out what the number is based on the whole array 
  //1X, 2X, 3X, 4X, 5X, 6X, 7X, 8X, 9X, 0X
//5. telling the motor to move based on the numberX
//6. Test and submit! 
