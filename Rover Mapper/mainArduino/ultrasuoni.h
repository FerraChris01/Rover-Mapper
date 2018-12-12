#define triggerPortDx 2
#define echoPortDx 6
#define triggerPortSx 10
#define echoPortSx 11
#define triggerPortF A0
#define echoPortF A1

class Ultrasuoni
{
private:
  int dDx;
  int dSx;
  int dF;
  
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
    dF =  dXA(A0, A1);
  }
  int dX(int t, int e)
  {   
    int ris;
    int durata = 0.0;
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
  int dXA(int t, int e)
  {   
    int ris;
    int durata = 0.0;
    digitalWrite(t, LOW);
    digitalWrite(t, HIGH);
    delayMicroseconds(10);
    digitalWrite(t, LOW);
 
    durata = pulseIn(e, HIGH);
 
    if(durata > 38000 )
      ris = -1;
    else
      ris = 0.034 * durata / 2;
    
    return ris;
   }
  

  int getFront()
  {
    return dF;
  }
  int getDx()
  {
    return dDx;
  }
  int getSx()
  {
    return dSx;
  }
  
    
  
};





