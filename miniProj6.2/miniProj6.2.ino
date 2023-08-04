const int colPins[4] = {23, 22, 14, 32};
const int rowPins[4] = {21, 17, 16, 19};
int curr_col = 0;
int curr_row = 0;
bool makeNote = false; 

const char keys[4][4] = {
'1','2','3','A',
'4','5','6','B',
'7','8','9','C',
'*','0','#','D'
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  scanPad();
  delay(100);

}
void scanPad(){
  for(int row=0; row<4; row++){
    pinMode(rowPins[row], OUTPUT);
    digitalWrite(rowPins[row], LOW);
    for(int col=0; col<4; col++){
      pinMode(colPins[col], INPUT);
      if(digitalRead(colPins[col])==LOW){
        curr_col = col;
        curr_row = row;
        makeNote = true;
      }
    }
    if(makeNote){
      Serial.println(keys[curr_row][curr_col]);
      makeNote = false;
    }
    digitalWrite(rowPins[row], HIGH);
  }
}
