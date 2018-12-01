#include <Bluetooth.h>

#include <bussola.h>

#include <ultrasuoni.h>

Bluetooth bt;

Ultrasuoni ultra;

Bussola bussola;

int direzioneGradi;

void setup() { 
  Serial.begin(9600);  
  bt = Bluetooth();
  bussola = Bussola();
  ultra = Ultrasuoni();
  direzioneGradi = bussola.getDegree();
  bussola.avanti();
  ultra.calcolaDistanze();
}

void loop() { 
  /*if (bussola.stoRuotando())                //il numero di distanze calcolate varia a seconda della velocità (del moto o angolare)
  { 
     bussola.checkRotation();
     ultra.calcolaDistanze();     
     bussola.checkRotation();
     bt.sendData(ultra.getDx(), ultra.getSx(), bussola.getDegree());
     bussola.checkRotation();
     direzioneGradi = bussola.getDegree();
  }  
  else
  {
    ultra.calcolaDistanze(); 
     //bt.sendData(ultra.getDx(), ultra.getSx(), bussola.getDegree());
     //bussola.straighten();
     trovaPercorsoMigliore(); 
  }    
  */
  if (bussola.stoRuotando())
  {
    bussola.checkRotation();
  }
  else
  {
   ultra.calcolaDistanze();
   trovaPercorsoMigliore(); 
  }

}

void trovaPercorsoMigliore() 
{
  if (ultra.getFront() < 13 && ultra.getFront() != - 1) 
  {
    bussola.stopMotors();
    bussola.routineRuotaDx(90);
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
