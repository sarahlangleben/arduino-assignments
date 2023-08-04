const int column_count = 8;
const int row_count = 8;
// The GPIO pins used for columns and rows
const int columns[column_count] = { 25,
                                    4, 5, 18, 12, 27, 33, 15 };
const int rows[row_count] = { 19, 16, 17, 21,
                              32, 14, 22, 23 };
//Big heart shape 1 means high and 0 meanslow
char input;
long timePassed; 

const int shape[8][8] = {
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
};
const int zero[8][8] = {
  0,0,1,1,1,1,0,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,0,1,1,1,1,0,0,
};
const int one[8][8] = {
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
};
const int two[8][8] = {
  0,0,1,1,1,1,0,0,
  0,1,0,0,0,0,1,0,
  0,0,0,0,0,0,1,0,
  0,0,0,0,1,1,0,0,
  0,0,0,1,0,0,0,0,
  0,0,1,0,0,0,0,0,
  0,0,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,
};
const int three[8][8] = {
  0,0,1,1,1,0,0,0,
  0,1,0,0,0,1,0,0,
  0,0,0,0,0,1,0,0,
  0,0,1,1,1,0,0,0,
  0,0,0,0,0,1,0,0,
  0,1,0,0,0,1,0,0,
  0,0,1,1,1,0,0,0,
  0,0,0,0,0,0,0,0,
};
const int four[8][8] = {
  0,1,0,0,1,0,0,0,
  0,1,0,0,1,0,0,0,
  0,1,0,0,1,0,0,0,
  0,1,1,1,1,1,0,0,
  0,0,0,0,1,0,0,0,
  0,0,0,0,1,0,0,0,
  0,0,0,0,1,0,0,0,
  0,0,0,0,1,0,0,0,
};
const int five[8][8] = {
  0,0,1,1,1,1,1,0,
  0,0,1,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,0,0,0,0,0,1,0,
  0,0,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,0,0,0,0,0,
};

const int six[8][8] = {
  0,0,0,1,1,1,0,0,
  0,0,1,0,0,0,1,0,
  0,0,1,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,0,1,0,0,0,1,0,
  0,0,1,0,0,0,1,0,
  0,0,0,1,1,1,0,0,
  0,0,0,0,0,0,0,0,
};
const int seven[8][8] = {
  0,1,1,1,1,1,1,0,
  0,0,0,0,0,0,1,0,
  0,0,0,0,0,1,0,0,
  0,0,0,0,1,0,0,0,
  0,0,0,1,0,0,0,0,
  0,0,0,1,0,0,0,0,
  0,0,0,1,0,0,0,0,
  0,0,0,1,0,0,0,0,
};
const int eight[8][8] = {
  0,0,1,1,1,1,0,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,0,1,1,1,1,0,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,0,0,0,0,0,
};
const int nine[8][8] = {
  0,0,1,1,1,1,0,0,
  0,1,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,0,1,1,1,1,1,0,
  0,0,0,0,0,0,1,0,
  0,1,0,0,0,0,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,0,0,0,0,0,
};

const int clear[8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};


void setup() {
  // Set all GPIOs to be output mode
  for (int i = 0; i < column_count; ++i) {
    pinMode(columns[i], OUTPUT);
  }
  for (int i = 0; i < row_count; ++i) {
    pinMode(rows[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  char input;
  long timePassed;
  if(Serial.available() > 0){
    input = Serial.read();
    Serial.println(input);
  }
  switch(input){
    case '0':
      while(input == '0'){
        drawZero();
        input = Serial.read();
      }
      // drawZero();
      // input = Serial.read();
      break;
    case '1':
      while(input == '1'){
        drawOne();
        input = Serial.read();
      }
      break;
    case '2':
      while(input == '2'){
        drawTwo();
        input = Serial.read();
      }
      break;
    case '3':
      while(input == '3'){
        drawThree();
        input = Serial.read();
      }
      break;
    case '4':
      while(input == '4'){
        drawFour();
        input = Serial.read();
      }
      break;
    case '5':
      while(input == '5'){
        drawFive();
        input = Serial.read();
      }
      break;
    case '6':
      while(input == '6'){
        drawSix();
        input = Serial.read();
      }
      break;
    case '7':
      while(input == '7'){
        drawSeven();
        input = Serial.read();
      }
      break;
    case '8':
      while(input == '8'){
        drawEight();
        input = Serial.read();
      }
      break;
    case '9':
      while(input == '9'){
        drawNine();
        input = Serial.read();
      }
      break;      
  }
}
    // case '7':
    //   while(input == '7'){
    //     drawSeven();
    //     input = Serial.read();
    //   }
    //   break;
    // case '8':
    //   while(input == '8'){
    //     drawEight();
    //     input = Serial.read();
    //   }
    //   break;
    // case '9':
    //   while(input == '9'){
    //     drawNine();
    //     input = Serial.read();
    //   }
    //   break;
// }

void drawZero() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], zero[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}

void drawOne() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], one[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}
void drawTwo() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], two[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}
void drawThree() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], three[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}
void drawFour() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], four[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}
void drawFive() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], five[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}
void drawSix() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], six[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}
void drawSeven() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], seven[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}
void drawEight() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], eight[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}
void drawNine() {
  //Iterate the row first
  for (int row = 0; row < row_count; ++row) {
    //Iterate the columan second
    for (int col = 0; col < column_count; ++col) {
      //Set high or low to the column line
      digitalWrite(columns[col], nine[row][col]);
    }
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], LOW);  // Turn on the row
    delay(2);
    digitalWrite(rows[row], HIGH);  //Turn off the row
    pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
  }
}
// void clearDisplay() {
//   //Iterate the row first
//   for (int row = 0; row < row_count; ++row) {
//     //Iterate the columan second
//     for (int col = 0; col < column_count; ++col) {
//       //Set high or low to the column line
//       digitalWrite(columns[col], clear[row][col]);
//     }
//     pinMode(rows[row], OUTPUT);
//     digitalWrite(rows[row], LOW);  // Turn on the row
//     delay(2);
//     digitalWrite(rows[row], HIGH);  //Turn off the row
//     pinMode(rows[row], INPUT);  // Avoid conflict with the Keypad input
//   }
// }