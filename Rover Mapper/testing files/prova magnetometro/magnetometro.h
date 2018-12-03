#include <motors.h>

#define dataPin 4
#define clockPin 5

class Magnetometro
{
  private: 
    Motors motori;   
    bool rotDx = false;
    bool rotSx = false;
    int angoloStart = 0;
    int gradiRot = 0;
  public:
   Magnetometro()
    {
      pinMode(magnData, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(magnData), checkRotation, CHANGE);    //magnetometro, angolo sta cambiando
    }
   bool stoRuotando()
	{
		if (rotDx || rotSx) return true;
		else return false;
	}
   void avanti()
   {
      motori.avanti();
   }
   void indietro()
   {
      motori.indietro();
   }
   void routineRuotaDx(int gradiP)
   {
    gradiRot = gradiP;
    //prendi angolo start;
    rotDx = true;
  }
  void routineRuotaSx(int gradiP)
  {
    gradiRot = gradiP;
    //prendi angolo start;
    rotSx = true;
  }
  bool checkRotation()
  {
    if (rotDx || rotSx)
    {
      if (rot Dx && (//(angolo attuale - angolostart) - angolo di rotazione >= 0))
      {
        motori.motorsOff();
        rotDx = false; 
        avanti();
      }
      else if (rot Sx && (//(angolo attuale - angolostart) - angolo di rotazione >= 0))
      {
        motori.motorsOff();
        rotSx = false; 
        avanti();
      }
    }
  }
};


