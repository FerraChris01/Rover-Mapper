
#include "Bluetooth.h"

#include "bussola.h"

#include "ultrasuoni.h" 

Bluetooth bt;

Ultrasuoni ultra;

Bussola* bussola;

int direzioneGradi;

void setup() { 
  Serial.begin(9600);  
  Serial.println("STARTED SERIAL");
//  bt = Bluetooth();
//  Serial.println("STARTED BT");
  bussola =  new Bussola();
//  Serial.println("STARTED BUSS");
//  ultra = Ultrasuoni();
//  Serial.println("STARTED US");
  direzioneGradi = bussola->getDegree();
  Serial.println("GRADI: "+String(direzioneGradi));
  bussola->avanti();
  ultra.calcolaDistanze();
  Serial.println("END SETUP");
  
}

void loop() { 
  if (bussola->stoRuotando())                //il numero di distanze calcolate varia a seconda della velocità (del moto o angolare)
  { 
     bussola->checkRotation();
     ultra.calcolaDistanze();     
     bussola->checkRotation();
     bt.sendData(ultra.getDx(), ultra.getSx(), bussola->getDegree());
     bussola->checkRotation();
     direzioneGradi = bussola->getDegree();
  }  
  else
  {
    ultra.calcolaDistanze(); 
     //bt.sendData(ultra.getDx(), ultra.getSx(), bussola.getDegree());
     Serial.println("Gradi: " + String(bussola->getDegree()));
     Serial.println(ultra.getDx());
     Serial.println(ultra.getSx());
     Serial.println(ultra.getFront());
     Serial.println("-------------------");
     //bussola.straighten();
     //trovaPercorsoMigliore(); 
  }    
  delay(500);

}

void trovaPercorsoMigliore() 
{
  if (ultra.getFront() < 13 && ultra.getFront() != - 1) 
  {
    bussola->stopMotors();
    bussola->routineRuotaDx(90);
  }
//  if (ultra.getDx() == -1)
 //    bussola.routineRuotaDx(90);
 // else if (ultra.getFront() < 13 && ultra.getDx() != -1)
 //   bussola.routineRuotaSx(180);
 // else if (ultra.getFront() < 13 && ultra.getSx() != -1)
//     bussola.routineRuotaDx(180); 
 // else if (ultra.getFront() < 13 && ultra.getDx() != -1)
 //    bussola.routineRuotaSx(90);
    
}
