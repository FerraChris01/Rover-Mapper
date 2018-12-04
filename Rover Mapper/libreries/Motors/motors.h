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
	  
	  analogWrite(enDx, 150);
      analogWrite(enSx, 150);  
    }
	void setSpeedMS(int sp) 
	{
		analogWrite(enDx, sp);
		analogWrite(enSx, sp);
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
		digitalWrite(avantiDx, HIGH);
		digitalWrite(avantiSx, HIGH);
	}
	void indietro()
	{
		motorsOff();
		digitalWrite(indietroDx, HIGH);
		digitalWrite(indietroSx, HIGH);
	}
	void ruotaSx()        
	{
		motorsOff();
		digitalWrite(avantiDx, HIGH);
		digitalWrite(indietroSx, HIGH);
	}
	void ruotaDx()       
	{
		motorsOff();
		digitalWrite(avantiSx, HIGH);
		digitalWrite(indietroDx, HIGH);
	}
    
};

