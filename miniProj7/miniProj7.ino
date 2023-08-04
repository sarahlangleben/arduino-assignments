#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int MPU_addr = 0x68;  // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission();

  Wire.beginTransmission(MPU_addr);  //I2C address of the MPU
  Wire.write(0x1B);                  //accessing the register 1B - gyroscope config
  Wire.write(0);                     //setting gyro to full scale
  Wire.endTransmission();

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);  //accessing the register 1C - accelerometer config
  Wire.write(0);     //setting the accel to +/-2g
  Wire.endTransmission();

  lcd.begin(23, 22);
  lcd.backlight();

  Serial.begin(9600);
}
void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);  // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // Sensitivity convertion to G unit  https://electronics.stackexchange.com/questions/39714/how-to-read-a-gyro-accelerometer
  float acclX = (float)AcX / 16384.0;
  float acclY = (float)AcY / 16384.0;
  float acclZ = (float)AcZ / 16384.0;

  //equation for temperature in degrees C from datasheet
  float temperature = Tmp / 340.00 + 36.53;

  float gyroX = (float)GyX / 131.0;
  float gyroY = (float)GyY / 131.0;
  float gyroZ = (float)GyZ / 131.0;

  if(acclY < 0.05){
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("|");
  }
  if(acclY < 0.40 && acclY > 0.30){
    lcd.clear();
    lcd.setCursor(8, 0);
    lcd.print("|");
  }
  if(acclY < 0.50 && acclY >= 0.40){
    lcd.clear();
    lcd.setCursor(9, 0);
    lcd.print("|");
  }
  if(acclY < 0.60 && acclY >= 0.50){
    lcd.clear();
    lcd.setCursor(10, 0);
    lcd.print("|");
  }
  if(acclY < 0.70 && acclY >= 0.60){
    lcd.clear();
    lcd.setCursor(11, 0);
    lcd.print("|");
  }
  if(acclY < .80 && acclY >= 0.70){
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print("|");
  }
  if(acclY < 0.90 && acclY >= 0.80){
    lcd.clear();
    lcd.setCursor(13, 0);
    lcd.print("|");
  }
  if(acclY < 0.95 && acclY >= 0.90){
    lcd.clear();
    lcd.setCursor(14, 0);
    lcd.print("|");
  }
  if(acclY > 0.95){
    lcd.clear();
    lcd.setCursor(15, 0);
    lcd.print("|");
  }
  if(acclY > -0.20 && acclY <= -0.05){
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("|");
  }
  if(acclY > -0.30 && acclY <= -0.20){
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("|");
  }
  if(acclY > -0.40 && acclY <= -0.30){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("|");
  }
  if(acclY > -0.50 && acclY <= -0.40){
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("|");
  }
  if(acclY > -0.60 && acclY <= -0.50){
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("|");
  }
  if(acclY > -0.70 && acclY <= -0.60){
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("|");
  }
  if(acclY < -0.71){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("|");
  }
  // if(acclY > -0.99 && acclY <= 0.70){
  //   lcd.clear();
  //   lcd.setCursor(0, 0);
  //   lcd.print("|");
  // }
  delay(1000);
}

