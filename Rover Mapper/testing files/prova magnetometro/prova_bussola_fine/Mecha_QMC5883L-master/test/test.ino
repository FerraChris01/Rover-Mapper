#include <Wire.h> //I2C Arduino Library

#define addr 0x0D //I2C Address for The HMC5883
float heading=0;

void setup() {

  Serial.begin(9600);  
  Wire.begin();


  Wire.beginTransmission(addr); //start talking
  Wire.write(0x0B); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x01); // Set the Register
  Wire.endTransmission();
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x09); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x1D); // Set the Register
  Wire.endTransmission();
}

void loop() {

  int x, y, z; //triple axis data

  //Tell the HMC what regist to begin writing data into


  Wire.beginTransmission(addr);
  Wire.write(0x00); //start with register 3.

  Wire.endTransmission();
  //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if (6 <= Wire.available()) {
    x = Wire.read(); //MSB  x
    x |= Wire.read() << 8; //LSB  x
    z = Wire.read(); //MSB  z
    z |= Wire.read() << 8; //LSB z
    y = Wire.read(); //MSB y
    y |= Wire.read() << 8; //LSB y
  }

  // Show Values
  //Serial.print("X Value: ");
  //Serial.println(x);
  //Serial.print("Y Value: ");
  //Serial.println(y);
  //Serial.print("Z Value: ");
  //Serial.println(z);
  //Serial.println();
  //heading = (int)(atan2(y, x) * 180 / M_PI);
  heading = (int)(atan2(x,z) * 180 / 3.14);
  
  if(heading<0){
    heading=headingTo360();  
  }

  Serial.println(heading);
  

  delay(500);
}

int headingTo360(){
  heading=360+heading;
  return heading;
}
