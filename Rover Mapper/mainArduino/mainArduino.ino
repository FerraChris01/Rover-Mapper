
#include "Bluetooth.h"

#include "bussola.h"

#include "ultrasuoni.h"

Bluetooth bt;

Ultrasuoni ultra;

Bussola* bussola;

int direzioneGradi;

int tStart = 0;
int tFine = 0;

int ledG = A2;
int ledR = A3;

#define k 50


void setup() {
  Serial.begin(9600);
  bussola =  new Bussola();
  direzioneGradi = bussola->getDegree();
  bussola->avanti();
  ultra.calcolaDistanze();
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);

}
void loop() {
  ultra.calcolaDistanze();
  bt.sendData(ultra.getDx(), ultra.getSx(), bussola->getDegree());
  if (bussola->stoRuotando()==true)
  {
    tFine = millis();
    if (tFine - tStart >= 1000)
    {
      digitalWrite(ledG, HIGH);
      digitalWrite(ledR, LOW);
      bussola->rotazioneFinita();
    }               
  }    
  else
  { 
      digitalWrite(ledG, LOW);
      digitalWrite(ledR, HIGH);
    frenaSeNecessario();
    trovaPercorsoMigliore();
  }
}
void frenaSeNecessario()
{
    if (ultra.getFront() < (k / 2) && ultra.getFront() != -1)
    {
      bussola->stopMotors();  
      bussola->routineRuotaDx();
    }
}
void trovaPercorsoMigliore()
{
//  if (ultra.getDx() > k || ultra.getDx() == -1)
//  {
//     bussola->routineRuotaDx();
//     tStart = millis();
//  }    
//  else if (ultra.getSx() > k || ultra.getSx() == -1)
//  {
//     bussola->routineRuotaSx();  
//     tStart = millis();      
//  }   
//  else if ((ultra.getFront() < (k / 2) && ultra.getFront() != -1) && ultra.getDx() < (k/2) && ultra.getSx() < (k/2))
//     bussola->stopMotors();

if(ultra.getFront()<(k/2) && ultra.getFront() != -1){
  if ((ultra.getSx() > ultra.getDx()) || ultra.getSx() == -1)
  {
     bussola->routineRuotaSx();  
     tStart = millis();      
  }   
  else if((ultra.getDx() > ultra.getSx()) || ultra.getDx() == -1){
    bussola->routineRuotaSx();
    tStart=millis();
  }
}

}
