#include "Bluetooth.h"

#include "bussola.h"

#include "ultrasuoni.h"

#include "motors.h"

Bluetooth bt;

Ultrasuoni ultra;

Motors motori;

Bussola* bussola;

int direzione = 0;
int tolleranza = 3;
bool rotazione = false;
int conta = 0;

int statoRover = 0;    // -1 STOP, 0 START, 1 SERIE DI ISTRUZIONI
String comando = "";
int istruzioneFlow = -1;
int valoreFlow = 0;
bool wait = false;

int led = A3;

#define Delay 770

#define k 30

void setup() {
  Serial.begin(9600);
  bussola =  new Bussola();
  pinMode(led, OUTPUT);
  direzione = bussola->getDegree();
  rotazione = false;
  motori.avanti();
}


void loop() {
//  setupRoutine();
  if (statoRover == 0)
  {
    inviaDati();
    vaiDritto();
 }
}

void vaiDritto()        //se sto andando a sbattere trova il percorso da prendere
{
  if (ultra.getFront() < (k / 2) && ultra.getFront() != -1) //se fine strada
  {
    digitalWrite(led, HIGH);
    if (ultra.getDx() < k / 2 && ultra.getSx() < k / 2)
      motori.motorsOff();
    else if (((ultra.getDx() > ultra.getSx()) && ultra.getDx() > k) || ultra.getDx() == -1)   //ruota DX
    {
      direzione =  (direzione + 90) % 360;
      motori.spinOrario();
      delay(Delay);
      motori.avanti();
    }
    else if (((ultra.getSx() > ultra.getDx()) && ultra.getSx() > k) || ultra.getSx() == -1)   //ruota SD
    {
      direzione = (direzione - 90 + 360) % 360;
      motori.spinAntiorario();
      delay(Delay);
      motori.avanti();
    }

  }
  digitalWrite(led, LOW);
}

void inviaDati()        // calcolo le distanze e le spedisco al pc
{
  ultra.calcolaDistanze();
  if (conta == 0)  //ivia solo ogni 4 rilevazioni
    bt.sendData(ultra.getDx(), ultra.getSx(), direzione, 1);
  else
    conta = (conta + 1) % 4;
}
void setupRoutine()
{
  bt.readData();
  if (bt.getNumEl() > 0)
  {
    comando = bt.popCommand();
    if (comando == "START")
    {
      motori.avanti();
      statoRover = 0;
    }
    else if (comando == "STOP")
    {
      motori.motorsOff();
      statoRover = -1;
    }
  }
}
