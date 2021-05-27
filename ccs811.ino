#include <Wire.h>
#define addr 0x5b

void setup() {
  //Wire.setSDA(PC1); //A4
  //Wire.setSCL(PC0); // A5
  Wire.begin();
  Serial.begin(9600);
  //Wire.beginTransmission(addr);
  //Wire.write(0xF4);
  //Wire.endTransmission();
  
  Wire.endTransmission();
  Wire.beginTransmission(addr);
  Wire.write(0x01);
  Wire.write(0x10);
  Wire.endTransmission();
  delay(100);
}

void loop() {
  uint8_t data[4];
  Wire.beginTransmission(addr);
  Wire.write(0x02);
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(addr,4);
  if (Wire.available() == 4)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
  }
  uint16_t CO2 = ((uint16_t)data[0] << 8) | data[1];
  uint16_t tVOC = ((uint16_t)data[2] << 8) | data[3];
  Serial.print("CO2=");
  Serial.print(CO2);
  Serial.print(" ppm ");
  Serial.print("     tVOC=");
  Serial.print(tVOC); 
  Serial.println(" ppb");
  delay(1000);
  
  /*Wire.beginTransmission(addr);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(addr,1);
  uint8_t data2 = Wire.read();
  Serial.print("status = ");
  Serial.println(data2);

  Wire.beginTransmission(addr);
  Wire.write(0xE0);
  Wire.endTransmission();
  Wire.requestFrom(addr,1);
  uint8_t data3 = Wire.read();
  Serial.print("error = ");
  Serial.println(data3);*/
}
