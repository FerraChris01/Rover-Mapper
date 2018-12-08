
#include "Bluetooth.h"

#include "bussola.h"

#include "ultrasuoni.h"

Bluetooth bt;

Ultrasuoni ultra;

Bussola* bussola;

int ledG = A2;
int ledR = A3;

int gradi = 0;

#define k 50


void setup() {
  Serial.begin(9600);
  bussola =  new Bussola();
  bussola->avanti();
  ultra.calcolaDistanze();
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW); 
}
void loop() {
  ultra.calcolaDistanze();
  gradi = bussola->getDegree();
  bt.sendData(ultra.getDx(), ultra.getSx(), bussola->getDegree());  
  if (ultra.getFront() < (k/2) && ultra.getFront() != -1)
    bussola->ruotaOrario(90);

}
void frenaSeNecessario()
{
  if (ultra.getFront() < (k / 2) && ultra.getFront() != -1)
    bussola->stopMotors();

}
void trovaPercorsoMigliore()
{

//  if (ultra.getFront() < (k / 2) && ultra.getFront() != -1)
//  {
//    if (ultra.getDx() < k / 2 && ultra.getSx() < k / 2 && ultra.getFront() < k / 2)
//      bussola->stopMotors();
//    else if ((ultra.getDx() > ultra.getSx()) || ultra.getDx() == -1)
//      bussola->ruotaOrario(90);
//    else if ((ultra.getSx() > ultra.getDx()) || ultra.getSx() == -1)
//      bussola->ruotaAntiorario(180);
//  }

}
