void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, LOW); //start with LED off
  //inputs: 123, 456, 7890
  int input;
  if(Serial.available() > 0){
    char input = Serial.read();
    Serial.write(input);
    switch(input) {
      case '1':
        space();
        dot();
        dash();
        dash();
        dash();
        dash();
        break;
      case '2':
        space();
        dot();
        dot();
        dash();
        dash();
        dash();
        break;
      case '3':
        space();
        dot();
        dot();
        dot();
        dash();
        dash();
        break;
      case '4':
        space();
        dot();
        dot();
        dot();
        dot();
        dash();
        break;
      case '5':
        space();
        dot();
        dot();
        dot();
        dot();
        dot();
        break;
      case '6':
        space();
        dash();
        dot();
        dot();
        dot();
        dot();
        break;
      case '7':
        space();
        dash();
        dash();
        dot();
        dot();
        dot();
        break;
      case '8':
        space();
        dash();
        dash();
        dash();
        dot();
        dot();
        break;
      case '9':
        space();
        dash();
        dash();
        dash();
        dash();
        dot();
        break;
      case '0':
        space();
        dash();
        dash();
        dash();
        dash();
        dash();
        break;   
    }
  }
}
void dot(){
   digitalWrite(LED_BUILTIN, HIGH);
   delay(300); //dot is 300 ms long
   digitalWrite(LED_BUILTIN, LOW);
   delay(300); //"space between two letters equal to one dot"
}
void dash(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(900); //"dash is equal to 3 dots"
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);//"space between two letters equal to one dot"
}
void space(){ 
  //"the space between two words is equal to seven dots" = 2100 ms
  digitalWrite(LED_BUILTIN, LOW);
  delay(2100);
}