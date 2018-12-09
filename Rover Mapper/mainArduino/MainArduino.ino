
#include "Bluetooth.h"

#include "bussola.h"

#include "ultrasuoni.h"

Bluetooth bt;

Ultrasuoni ultra;

Bussola* bussola;

int direzione;
float tolleranza = 5;

int statoRover = -2;    // -1 STOP, 0 START, 1 SERIE DI ISTRUZIONI
String comando = "";

int istruzioneFlow = -1;
int valoreFlow = 0;
bool wait = false;
int tStart;

#define k 50


void setup() {
  Serial.begin(9600);
  bussola =  new Bussola();
  bussola->avanti();

  //direzione = bussola->getDegree();
  //digitalWrite(A2, HIGH);
}

void loop()
{
      
  float doveSonoIo = bussola->getDegree();
  float doveDevoAndare=bussola->getSomma(doveSonoIo,90);
  bussola->avanti();
  ultra.calcolaDistanze();
  
  if (ultra.getFront() < (k / 2) && ultra.getFront() != -1)       //relevato ostacolo davanti
  {
    Serial.println("OSTACOLOOOOOO");
    bussola->stopMotors();  //spengo tutto
    //Mi sposto a dx

    int delta = doveDevoAndare - bussola->getDegree(); 
    //while (vedo se sono arrivato){
      delta = direzione - bussola->getDegree();
      
     ultra.calcolaDistanze();
     bussola->rotazione(doveDevoAndare); 
    //}
    
  }
      

}

//    setupRoutine();
//    if (statoRover == 0)
//    {
//      mainRoutine();
//      //    if (bussola->stoRuotando())
//      //      //rotazione;
//      //    else
//      //    {
//      trovaPercorso();
//      Serial.println(bussola->getDegree());
//      bussola->straighten(180);
//      //correggiRotta();
//      //}
//    }
//    else if (statoRover == 1)
//    {
//      if (bt.getNumEl() > 0 && !wait)
//        decodeCommand(bt.popCommand());
//  
//      mainRoutine();
//      routineFlow();
//    }



void setupRoutine()
{
  bt.readData();
  if (bt.getNumEl() > 0)
  {
    comando = bt.popCommand();
    if (comando == "START")
    {
      bussola->avanti();
      statoRover = 0;
    }
    else if (comando == "STOP")
    {
      bussola->stopMotors();
      statoRover = -1;
    }
    else if (comando == "FLOW")
    {
      bussola->stopMotors();
      statoRover = 1;
    }
    else if (comando == "ENDFLOW")
    {
      bussola->avanti();
      bt.resetArray();
      statoRover = 0;
    }
  }
}
void mainRoutine()
{
  ultra.calcolaDistanze();
  bt.sendData(ultra.getDx(), ultra.getSx(), bussola->getDegree(), (bussola->stoRuotando()) ? -1 : bussola->getSpeedMotors());
  
}

void trovaPercorso()
{
  float doveSonoIo = bussola->getDegree();
  float doveDevoAndare=bussola->getSomma(doveSonoIo,90);
  
  if (ultra.getFront() < (k / 2) && ultra.getFront() != -1)       //relevato ostacolo davanti
  {
    bussola->stopMotors();  //spengo tutto
    //Mi sposto a dx
    bussola->straighten(doveDevoAndare,false);
    
//    if (ultra.getDx() < k / 2 && ultra.getSx() < k / 2 && ultra.getFront() < k / 2)
//      bussola->stopMotors();
//    else if ((ultra.getDx() > ultra.getSx()) || ultra.getDx() == -1)
//      direzione += 90;
//    else if ((ultra.getSx() > ultra.getDx()) || ultra.getSx() == -1)
//      direzione -= 90;
  }
}

void correggiRotta()
{
  //correggi rotta
  int delta = direzione - bussola->getDegree();     // ATTENZIONE ALLO 0
  int angolo = (delta > 180 ? delta - 360 : (delta < -180) ? delta + 360 : delta);
  if (fabs(angolo) > tolleranza)
  {
    if (angolo < 0)      //sto andando verso destra
      bussola->setSpeedMotors(100 - fabs(angolo), 100 + fabs(angolo)); //se sto andando a destra tento di andare a sinsitra
    else                //sto andando verso sinistra
      bussola->setSpeedMotors(100 + fabs(angolo), 100 - fabs(angolo)); //se sto andando a sinsitra tento di andare a destra
  }
  else                  //differenza tollerabile
    bussola->setSpeedMotors(100, 100);
}
void routineFlow()
{
  switch (istruzioneFlow)
  {
    case 0:
      if (millis() - tStart >= valoreFlow) wait = false;
      break;

      //TODO altri casi
  }
}
void decodeCommand(String par)
{
  String ris = par.substring(0, 2);
  int valoreFlow =  par.substring(2, par.length()).toInt();
  if (ris == "FW")    //avanti
  {
    istruzioneFlow = 0;
    bussola->avanti();
    tStart = millis();
  }
  else if (ris ==  "RD")   //ruota a destra
  {
    istruzioneFlow = 1;
    //avvio rotazione
  }
  else if (ris == "RS")    //ruota a sinistra
  {
    istruzioneFlow = 2;
    //avvio rotazione
  }
  else if (ris == "SP")   //stop motori
  {
    wait = false;
    bussola->stopMotors();
  }
  else if (ris == "ED")     //fine flow
  {
    wait = false;
    bussola->avanti();
    statoRover = 0;
  }
}
