#include <LiquidCrystal_I2C.h>
#include <SPI.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); 

const int CS_pin = A0;
// Transaction specifiers CTRL 1-5 for
const byte WRITE = 0b00000000;
const byte READ = 0b10000000;
const byte MULTI_READ = 0b01000000;
// Register 1-5 store the setting of the sensor
const byte CTRL1 = 0x20;
const byte XY_MODE_LOW = 0b00000000;
const byte REFRESH_10Hz = 0b00010000;
const byte CTRL2 = 0x21;
const byte FULL_SCALE_16GAUSS = 0b01100000;
const byte FULL_SCALE_4GAUSS = 0b00000000;
const byte CTRL3 = 0x22;
const byte OPERATING_MODE_SINGLE = 0b00000001;
const byte OPERATING_MODE_CONT = 0b00000000;
const byte CTRL4 = 0x23;
const byte Z_MODE_LOW = 0b00000000;
const byte CTRL5 = 0x24;
const byte BLOCK_DATA_UPDATE_ON = 0b01000000;
const byte OUT_X_L = 0x28;
const byte OUT_Y_L = 0x2A;
const byte OUT_Z_L = 0x2C;
void setup() {
  Serial.begin(9600);
  lcd.begin(23, 22);
  lcd.backlight();
  lcd.setCursor(0, 0);

  // CS signal
  pinMode(CS_pin, OUTPUT);
  // setting the SPI system
  digitalWrite(CS_pin, HIGH);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.begin();
  // setting CTRL1 10Hz sampling rate
  digitalWrite(CS_pin, LOW);
  SPI.transfer(WRITE | CTRL1);
  SPI.transfer(XY_MODE_LOW | REFRESH_10Hz);
  digitalWrite(CS_pin, HIGH);
  // setting CTRL2 for +/-4 Gauss range
  digitalWrite(CS_pin, LOW);
  SPI.transfer(WRITE | CTRL2);
  SPI.transfer(FULL_SCALE_4GAUSS);
  digitalWrite(CS_pin, HIGH);
  // setting CTRL3 for continuous operations
  digitalWrite(CS_pin, LOW);
  SPI.transfer(WRITE | CTRL3);
  SPI.transfer(OPERATING_MODE_CONT);
  digitalWrite(CS_pin, HIGH);
  // setting CTRL4 for Z
  digitalWrite(CS_pin, LOW);
  SPI.transfer(WRITE | CTRL4);
  SPI.transfer(Z_MODE_LOW);
  digitalWrite(CS_pin, HIGH);
  // setting CTRL5 for synchronization
  digitalWrite(CS_pin, LOW);
  SPI.transfer(WRITE | CTRL5);
  SPI.transfer(BLOCK_DATA_UPDATE_ON);
  digitalWrite(CS_pin, HIGH);
  Serial.begin(9600);
}
void loop() {  
  int16_t gauss_x;  // Hexadecimal
  digitalWrite(CS_pin, LOW);
  SPI.transfer(READ | OUT_X_L | MULTI_READ);
  // Receive the LSB
  gauss_x = SPI.transfer(0);
  // Receive the MSB and combine it with LSB
  gauss_x = SPI.transfer(0) * 256 + gauss_x;
  digitalWrite(CS_pin, HIGH);
  // print the result
  lcd.print((400.0 * gauss_x) / 0x7FFF);

  lcd.setCursor(0, 1);
  int16_t gauss_y;  // Hexadecimal
  digitalWrite(CS_pin, LOW);
  SPI.transfer(READ | OUT_Y_L | MULTI_READ);
  // Receive the LSB
  gauss_y = SPI.transfer(0);
  // Receive the MSB and combine it with LSB
  gauss_y = SPI.transfer(0) * 256 + gauss_y;
  digitalWrite(CS_pin, HIGH);
  // print the result
  lcd.print((400.0 * gauss_y) / 0x7FFF);

  lcd.setCursor(8, 0);
  int16_t gauss_z;  // Hexadecimal
  digitalWrite(CS_pin, LOW);
  SPI.transfer(READ | OUT_Z_L | MULTI_READ);
  // Receive the LSB
  gauss_z = SPI.transfer(0);
  // Receive the MSB and combine it with LSB
  gauss_z = SPI.transfer(0) * 256 + gauss_z;
  digitalWrite(CS_pin, HIGH);
  // print the result
  lcd.print((400.0 * gauss_z) / 0x7FFF);
  delay(1000);
  lcd.clear();
}