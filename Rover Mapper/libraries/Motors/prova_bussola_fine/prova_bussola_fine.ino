#include <Wire.h>
#include <MechaQMC5883.h>

int heading = 0;

MechaQMC5883 qmc;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  //qmc.init();
  qmc.setMode(Mode_Continuous,ODR_10Hz,RNG_8G,OSR_512);
}

void loop() {
  int x,y,z;
  qmc.read(&x,&y,&z);

  heading = (int)(atan2(y,x) * 180 / 3.14) + 180;

  Serial.println(heading);  

  delay(100);
}

/*
   int headingTo360(int gradi){
   if(gradi<0)   gradi=360+gradi;
   gradi += 720;
   gradi = gradi % 360;
  return gradi;
}

int To360(int gradi){
  gradi += 180;
  return gradi;
}
*/
