#include <motors.h>

#include <Bluetooth.h>

#include <ultrasuoni.h>

Bluetooth bt;

Ultrasuoni ultra;

Motors motori;

float velocita = 0.0;

void setup() {
  Serial.begin(9600);
  bt = Bluetooth();
  ultra = Ultrasuoni();
  motori = Motors();
}

void loop() {
  delay(1000);
  calibra();
  bt.testSpeed(velocita);  
  while (1);
}

void calibra()      //posizionare il rover almeno a 1.5 metri di distanza dal muro
{
  float disStart = ultra.testSpeed();
  motori.avanti();  
  int tStart = millis();
  while (millis() - tStart < 1000);
  float distFine = ultra.testSpeed();
  motori.motorsOff();
  velocita = (distFine - disStart) * 0.01;
}
