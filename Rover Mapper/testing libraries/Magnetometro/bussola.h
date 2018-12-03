#include <Wire.h> //I2C Arduino LibraryLibrary
#define addr 0x1E //I2C Address for The HMC5883
#include <motors.h>

#define dataPin A4
#define clockPin A5

class Bussola
{
private:
	Motors motori;
	bool rotDx;
	bool rotSx;
	int angoloStart;
	int gradiRot;

public:
	Magnetometro()
	{
		motori = Motors();
		rotDx = false;
	    rotSx = false;
		angoloStart = 0;
		gradiRot = 0;

		Serial.begin(9600);
		Wire.begin();

		Wire.beginTransmission(addr); //start talking
		Wire.write(0x02); // Set the Register
		Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
		Wire.endTransmission();

		pinMode(dataPin, INPUT_PULLUP);
	}
	int getDegree()
	{
		int heading, x, y, z;
		heading = x = y = z = 0;
		//Tell the HMC what regist to begin writing data into
		Wire.beginTransmission(addr);
		Wire.write(0x03); //start with register 3.
		Wire.endTransmission();


		//Read the data.. 2 bytes for each axis.. 6 total bytes
		Wire.requestFrom(addr, 6);
		if (6 <= Wire.available()) 
		{
			x = Wire.read() << 8; //MSB  x 
			x |= Wire.read(); //LSB  x
			z = Wire.read() << 8; //MSB  z
			z |= Wire.read(); //LSB z
			y = Wire.read() << 8; //MSB y
			y |= Wire.read(); //LSB y
		}
		heading = (int)(atan2(y, x) * 180 / M_PI);

		return heading;
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
	        motori.motorsOff();
			rotDx = false;
		}
		else if (rotSx && ((getDegree() + gradiRot) >= angoloStart))
		{
		    motori.motorsOff();
			rotSx = false;
		}		
	}
};


