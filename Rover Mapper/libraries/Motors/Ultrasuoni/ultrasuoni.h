#define triggerPortDx 2
#define echoPortDx 6
#define triggerPortSx 10
#define echoPortSx 11
#define triggerPortF A0
#define echoPortF A1

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
		int porteT[3] = {2, 10, A0};
		int porteR[3] = {6, 11, A1};
		float durate[3];
		float risultati[3];
		for (int i = 0; i < 3; i++)		
			digitalWrite(porteT[i], LOW );
		
		for (int i = 0; i < 3; i++)
			digitalWrite(porteT[i], HIGH );		
		
		delayMicroseconds(10);
		
		for (int i = 0; i < 3; i++)
			digitalWrite(porteT[i], LOW );	
		
		for (int i = 0; i < 3; i++)
			durate[i] = pulseIn(porteR[i], HIGH );
		
		for (int i = 0; i < 3; i++)
		{
			if(durate[i] > 38000 )
				risultati[i] = -1;
			else
				risultati[i] = 0.034 * durate[i] / 2;
		}
		dDx = risultati[0];
		dSx = risultati[1];
		dF = risultati[2];	
		
	}
	
	float testSpeed()
	{
		float ris;
		float durata = 0.0;
		digitalWrite(A0, LOW);
		digitalWrite(A0, HIGH);
		delayMicroseconds(10);
		digitalWrite(A0, LOW);
 
		durata = pulseIn(A1, HIGH);
 
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
	
		
	
};




