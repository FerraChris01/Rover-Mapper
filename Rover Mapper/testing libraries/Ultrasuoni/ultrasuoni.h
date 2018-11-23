#define triggerPortDx 2
#define echoPortDx 6
#define triggerPortSx 10
#define echoPortSx 11
#define triggerPortF 12
#define echoPortF 13

class Ultrasuoni
{
private:
	float dDx;
	float dSx;
	float dF;
public:
	Ultrasuoni()
	{
		pinMode(triggerPortF, OUTPUT);
		pinMode(echoPortF, INPUT);
		pinMode(triggerPortDx, OUTPUT);
		pinMode(echoPortDx, INPUT);
		pinMode(triggerPortSx, OUTPUT);
		pinMode(echoPortSx, INPUT);
		Serial.begin(9600);
	}
	void calcolaDistanze()
	{	
		dDx = dX(2, 6);		
		dSx = dX(10, 11);
		dF =  dX(12, 13);
	}
	float dX(int t, int e)
	{		
		float ris;
		float durata = 0.0;
		digitalWrite(t, LOW );
		digitalWrite(t, HIGH );
		delayMicroseconds(10);
		digitalWrite(t, LOW );
 
		durata = pulseIn(e, HIGH );
 
		if(durata > 38000 )
			ris = -1;
		else
			ris = 0.034 * durata / 2;
		
		return ris;
	}

	float getFront()
	{
		return dF;
	}
	float getDx()
	{
		return dDx;
	}
	float getSx()
	{
		return dSx;
	}
	
	void sendDxSx()
	{
		Serial.println((String)dDx + "/" + (String)dSx);
	}
		
	
};




