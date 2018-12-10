#define avantiDx 7
#define indietroDx 8  
#define avantiSx 4	
#define indietroSx 5 	  
#define enSx 9	
#define enDx 3

class Motors 
{
  private:
    float spDx;
    float spSx;
    
  public:
    Motors() 
    { 
	  pinMode (avantiDx, OUTPUT);
	  pinMode (indietroDx, OUTPUT);
	  pinMode (indietroSx, OUTPUT);
	  pinMode (avantiSx, OUTPUT);
	  pinMode (enDx, OUTPUT);
	  pinMode (enSx, OUTPUT);

    spDx = spSx = 100;    
	  analogWrite(enDx, spDx);
    analogWrite(enSx, spSx);  
    }
	void setSpeedMS(float dx, float sx) 
	{
    spDx = dx;
    spSx = sx;
		analogWrite(enDx, spDx);
		analogWrite(enSx, spSx);
	}
 float getDx(){
  return spDx;
 }
 float getSx(){
  return spSx;
 }
  int getSpeedMS()
  {
    return ((spDx + spSx) / 2);
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
	void spinOrario()        
	{
		motorsOff();
		digitalWrite(avantiDx, HIGH);
		digitalWrite(indietroSx, HIGH);
	}
	void spinAntiorario()       
	{
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
