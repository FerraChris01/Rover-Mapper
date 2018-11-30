#include <Wire.h> 

#include <motors.h>

#include <MechaQMC5883.h>

class Bussola
{
private:
	Motors motori = Motors();
	MechaQMC5883 qmc = MechaQMC5883();
	bool rotDx;
	bool rotSx;
	int angoloStart;
	int gradiRot;


public:
	Bussola()
	{
		rotDx = false;
	     rotSx = false;
		angoloStart = 0;
		gradiRot = 0;
		
		Wire.begin();
		Serial.begin(9600);
		//qmc.init();
	}
	int getDegree()
	{
		int x,y,z,heading;
		qmc.read(&x,&y,&z);

		heading = (int)(atan2(y,x) * 180 / 3.14) + 180;

		return heading;
	}
	void straighten(int direzione)
	{
		//if (direzione > getDegree())
			// portati a destra
		//else if (direzione < getDegree())
			// portati a sinistra
		
	}
	void avanti()
	{
		motori.avanti();
	}
	void indietro()
	{
		motori.indietro();
	}
	void stopMotors()
	{
		motori.motorsOff();
	}
	void routineRuotaDx(int gradiP)
	{
		gradiRot = gradiP;
		angoloStart = getDegree();
		rotDx = true;
		motori.ruotaDx();
	}
	void routineRuotaSx(int gradiP)
	{
		gradiRot = gradiP;
		angoloStart = getDegree();
		rotSx = true;
		motori.ruotaSx();
	}
	bool stoRuotando()
	{
		if (rotDx || rotSx) return true;
		else return false;
	}
	void checkRotation()
	{
		if (rotDx && ((getDegree() - angoloStart) >= gradiRot))
		{	        
			rotDx = false;
			motori.avanti();
		}
		else if (rotSx && ((getDegree() + gradiRot) >= angoloStart))
		{		    
			rotSx = false;
			motori.avanti();
		}		
	}
};


