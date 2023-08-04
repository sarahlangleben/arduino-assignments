unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 5000;
unsigned long pressTime;
unsigned long liftTime;
unsigned long lengthOfPress;
byte currentButtonState;
byte previousButtonState;
int count = 0;
boolean counting; 
//const int led = 13;// Pin for LED
const int buttonPin = 21; //GPIO 21 for Button
// the setup routine runs once when you press reset:

void setup() {                
// initialize the digital pin as an output and input
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); 
  counting=true;
  startMillis=millis(); 
}
// the loop routine runs over and over again forever:
void loop() {
  //if(digitalRead(buttonPin) == LOW){Serial.println("button pressed");}
  //currentButtonState=digitalRead(buttonPin);
  currentMillis = millis();
  previousButtonState = currentButtonState; //remember this loops
  currentButtonState = digitalRead(buttonPin);
  if(currentButtonState != previousButtonState){ //state change
    pressTime = currentMillis;
    if(currentButtonState == LOW){
      count++; //raw number of times button has been pressed-- NOT LENGTH OF PRESS
      Serial.println(count);
    }
    if(currentButtonState==HIGH and previousButtonState==LOW){
      liftTime = currentMillis;
      lengthOfPress = liftTime - pressTime;
      Serial.println(lengthOfPress)
    }
  }
}

  // if(currentMillis-startMillis <= period){
  //   currentButtonState = digitalRead(buttonPin);
  //   if(currentButtonState == LOW and previousButtonState == HIGH){
  //     count++;
  //     Serial.println(count);
  //   }
  // }
  // else{
  //   if(counting==true){
  //     Serial.println("time is up");
  //     counting=false;
  //   }
  //if(digitalRead(buttonPin) == LOW){Serial.println("button pressed");}
//make function that checks how long a button is pressed, returns that number
//isDash(), isDot(), these will return booleans based on the number being < or > a certain number. 

//1. get a count of button presses X
//2. time how long a button is pressed X
//3. differentiate between the two: how long is a dash, how long a dot? X
//4. translate the individual presses
  //4.1 count how many presses-- max is five, once you hit five you can change motor speed X
  //4.3 after five presses, call individual motor control methods and reset count = 0. X
  //4.4 track idle time-- if over 10 seconds no press resent counter X
  //4.5 figuring out what the number is based on the whole array:
    // loop through the whole thing (you might have to make a method for each number)
    //
