#include <Wire.h>

#ifndef Mecha_QMC5883
#include "MechaQMC5883.h"
#endif

class Bussola
{
  private:
    MechaQMC5883 qmc;

  public:
    Bussola()
    {
      Wire.begin();

      qmc.setMode(Mode_Continuous, ODR_200Hz, RNG_8G, OSR_512);

      Serial.begin(9600);
      qmc.init();
    }
    int getDegree()
    {
      int x, y, z, heading;
      qmc.read(&x, &y, &z);

      heading = (int)(atan2(y, x) * 180 / 3.14) + 180;

      return heading;
    }

};
