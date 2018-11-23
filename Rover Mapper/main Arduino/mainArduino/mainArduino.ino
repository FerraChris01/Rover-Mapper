#include <bussola.h>

#include <ultrasuoni.h>

Ultrasuoni ultra;

Bussola bussola;

void setup() { 
  Serial.begin(9600);  
  bussola.avanti();
}

void loop() { 
  if (bussola.stoRuotando())                //il numero di distanze calcolate varia a seconda della velocità (del moto o angolare)
  { 
     bussola.checkRotation();
     ultra.calcolaDistanze();     
     bussola.checkRotation();
     ultra.sendDxSx();
     bussola.checkRotation();
  }
  else
  {
     ultra.calcolaDistanze();  
     ultra.sendDxSx();
     //delay maggiore
     trovaPercorsoMigliore(); 
  }       
}

void trovaPercorsoMigliore() {
  //si deve sempre fare una media tra distanza a destra e sinistra NECESSARIO SENSORE POSTERIORE
  if (ultra.getFront() < 10 && ultra.getFront() != - 1) bussola.stopMotors();
  //if (ultra.getDx() == -1)
  //   bussola.routineRuotaDx(90);
 // else if (ultra.getFront() < 5 && ultra.getDx() != -1)
 //   bussola.routineRuotaSx(180);
  //else if (ultra.getFront() < 5 && ultra.getSx() != -1)
  //   bussola.routineRuotaDx(180); 
  //else if (ultra.getFront() < 5 && ultra.getDx() != -1)
   //  bussola.routineRuotaSx(90);
}
