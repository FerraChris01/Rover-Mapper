#define avantiDx 7
#define indietroDx 8  
#define avantiSx 4	
#define indietroSx 5 	  
#define enSx 9	
#define enDx 3

class Motors 
{
  public:
    Motors() 
    { 
	  pinMode (avantiDx, OUTPUT);
	  pinMode (indietroDx, OUTPUT);
	  pinMode (indietroSx, OUTPUT);
	  pinMode (avantiSx, OUTPUT);
	  pinMode (enDx, OUTPUT);
	  pinMode (enSx, OUTPUT);
   	  
	  analogWrite(enDx, 100);
    analogWrite(enSx, 100);  
    }
	void setSpeedMS(int spDx, int spSx) 
	{
		analogWrite(enDx, spDx);
		analogWrite(enSx, spSx);
	}
	void motorsOff()
	{
		digitalWrite(avantiDx, LOW);
		digitalWrite(avantiSx, LOW);
		digitalWrite(indietroDx, LOW);
		digitalWrite(indietroSx, LOW);
	}
	void avanti() 
	{
    motorsOff();
    setSpeedMS(100,100);
		digitalWrite(avantiDx, HIGH);
		digitalWrite(avantiSx, HIGH);
    delay(100);
    setSpeedMS(70,70);
	}
	void indietro()
	{
		motorsOff();
		digitalWrite(indietroDx, HIGH);
		digitalWrite(indietroSx, HIGH);
	}
	void spinAntiorario()        
	{
    setSpeedMS(150,150);
		motorsOff();
		digitalWrite(avantiDx, HIGH);
		digitalWrite(indietroSx, HIGH);
	}
	void spinOrario()       
	{
    setSpeedMS(150,150);
		motorsOff();
		digitalWrite(avantiSx, HIGH);
		digitalWrite(indietroDx, HIGH);
	}
	void ruotaDx()
	{
		motorsOff();
		digitalWrite(avantiSx, HIGH);
	}
	void ruotaSx()
	{
		motorsOff();
		digitalWrite(avantiDx, HIGH);
	}
    
};
