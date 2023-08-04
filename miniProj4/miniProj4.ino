#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); 
const int TC74_address = 0b1001011;

void setup() {
  // open the serial port
  Serial.begin(9600);
  // Start the I2C module
  Wire.begin();
  lcd.begin(23, 22);
  lcd.backlight();
  lcd.setCursor(0, 0);
}
void loop() {
  // start a transmission to the TC74
  Wire.beginTransmission(TC74_address);
  // request register 0 (i.e. the temperature)
  Wire.write((byte)0);
  // End transmission
  Wire.endTransmission();
  // prepare to receive on byte
  Wire.requestFrom(TC74_address, 1);
  lcd.print(Wire.read(), DEC);
  delay(1000);
  lcd.clear();
}