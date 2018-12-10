#include <Wire.h>

#include "motors.h"

#ifndef Mecha_QMC5883
#include "MechaQMC5883.h"
#endif


int ledG = A2;
int ledR = A3;


class Bussola
{
  private:
    Motors motori;
    MechaQMC5883 qmc;
    float angoloStart;
    float gradiArrivo;
    float gradiRot;
    float gradiToMove = -1;
    bool rotazione = false;
    //bool particolare = false;

  public:
    Bussola()
    {
      Wire.begin();

      qmc.setMode(Mode_Continuous, ODR_200Hz, RNG_8G, OSR_512);

      motori = Motors();


      int ledG = A2;
      int ledR = A3;


      Serial.begin(9600);
      qmc.init();
    }
    float getDegree()
    {
      int x, y, z, heading;
      qmc.read(&x, &y, &z);

      heading = (atan2(y, x) * 180 / 3.14) + 180;

      return heading;
    }
    void setSpeedMotors(int dx, int sx)
    {
      motori.setSpeedMS(dx, sx);
    }
    int getSpeedMotors()
    {
      return motori.getSpeedMS();
    }


    void straighten(float direzione)
    {

      //90
      //Sono a 200
      //-110

      //correggi rotta
      int delta = direzione - getDegree();     // ATTENZIONE ALLO 0
      int angolo = (delta > 180 ? delta - 360 : (delta < -180) ? delta + 360 : delta);

      if (fabs(delta) > 3) //tolleranza
      {

        int dir = getDirezioneDaFare(getDegree(), direzione);
        if (dir == 2) {     //sto andando verso destra
          //motori.setSpeedMS(100 + abs(delta), 100 - abs(delta)); //se sto andando a destra tento di andare a sinsitra
          motori.ruotaSx();


        }else{              //sto andando verso sinistra
          //motori.setSpeedMS(100 - abs(delta), 100 + abs(delta)); //se sto andando a sinsitra tento di andare a destra
          motori.ruotaDx();

        }
      }else {
          //differenza tollerabile
          motori.avanti();
          motori.setSpeedMS(100, 100);
          Serial.println("ARRIVATO!!!");
        }





      }


      void rotazioneOstacolo(float direzione) {
        int delta = direzione - getDegree();     // ATTENZIONE ALLO 0
        int angolo = (delta > 180 ? delta - 360 : (delta < -180) ? delta + 360 : delta);

        if (fabs(delta) > 3) //tolleranza
        {

          int dir = getDirezioneDaFare(getDegree(), direzione);
          if (dir == 2) {     //sto andando verso destra
            //motori.setSpeedMS(100 + abs(delta), 100 - abs(delta)); //se sto andando a destra tento di andare a sinsitra
            motori.spinAntiorario();

          }
          else {               //sto andando verso sinistra
            //motori.setSpeedMS(100 - abs(delta), 100 + abs(delta)); //se sto andando a sinsitra tento di andare a destra
            motori.spinOrario();
          }
        }
        else {
          //differenza tollerabile
          motori.avanti();
          motori.setSpeedMS(100, 100);
          Serial.println("ARRIVATO!!!");
        }

      }


      boolean versoCorretto(int direzione) {
        //@Author Saccani
        //Dice se sono nella direzione giusta
        int gradiEffettivi = getDegree();//350


        //Caso Particolare???
        //Sono tra 0-5 o 355-360?
        if ((direzione <= 2 && direzione >= 0) || (direzione >= 358 && direzione <= 360)) {
          if (gradiEffettivi >= getSottrazione(direzione, 2)) {
            return true;
          } else {
            if (gradiEffettivi <= getSomma(direzione, 2)) {
              return true;
            } else {
              //particolare = true;
              return false;
            }
          }
        } else if (gradiEffettivi <= getSomma(direzione, 2) && gradiEffettivi >= getSottrazione(direzione, 2)) { //Sono quindi in una situazione normale
          return true;
        } else {
          return false;
        }

      }

      int correggi(int gradi) {
        //@Author Saccani
        //Tipo: 350 ---> diventa 10
        return 360 - gradi;
      }

      int getSottrazione(int direzione, int diTot) {
        //@Author Saccani
        int ris = direzione - diTot;

        if (ris < 0) {
          //Sono andato indietro di 0 gradi, trovo il corrispettivo
          //Esempio:  direzione=0   diTot=5 ---> ris=-5   -->correggo in 355
          ris = 360 + ris;
        }
        return ris;
      }

      int getSomma(int direzione, int diTot) {
        //@Author Saccani
        int ris = direzione + diTot;

        if (ris > 360) {
          //Ho superato i 360, trovo il corrispettivo
          //Esempio:  direzione=360   diTot=5 ---> ris=365   -->correggo in 5
          ris = ris - 360;
        }
        return ris;
      }



      void avanti()
      {
        motori.avanti();
      }
      void indietro()
      {
        motori.indietro();
      }
      void stopMotors()
      {
        motori.motorsOff();
      }
      void ruotaOrario(float gradiP)
      {
        gradiArrivo = (int)(getDegree() + gradiP) % 360;
        rotazione = true;

      }

      void ruotaAntiorario(float gradiP)
      {
        gradiArrivo = (int)(getDegree() - gradiP + 360) % 360;
        rotazione = true;
      }

      bool stoRuotando()
      {
        if (rotazione) return true;
        else return false;
      }
      int getGradiRot()
      {
        return gradiArrivo;
      }
      void testSpeed()
      {
        motori.spinOrario();
      }
      //@author mattia broch
      //metodo che dato un angolo iniziale e finale ritorna una stringa con ANTI o ORARIO per indicare la rotazione
      //e l'angolo alfa di rotazione
      String setDirezione(int start, int finale) {
        int ris1 = getRis1(start, finale);
        int ris2 = getRis2(start, finale);
        if (ris1 < ris2) {
          if (ris1 > 0) {
            return "anti";
          }
          else return "orario";
        }
        else {
          if (ris2 > 0) {
            return "anti";
          }
          else return "orario";
        }

      }


      int getQuadrante(int gradi) {
        if (gradi >= 0 && gradi <= 90) {
          return 1;
        } else if (gradi >= 91 && gradi <= 180) {
          return 2;
        } else if (gradi >= 181 && gradi <= 270) {
          return 3;
        } else if (gradi >= 271 && gradi <= 360) {
          return 4;
        }
      }

      //se ritorna 1 = orario altrimenti se ritorna 2 = antiorario
      int getDirezioneDaFare(int doveSonoIo, int doveDevoArrivare) {
        int attualeQuad =  getQuadrante(doveSonoIo);
        int arrivoQuad =  getQuadrante(doveDevoArrivare);
        int ris = -1;

        if (attualeQuad == arrivoQuad) {
          //caso semplice
          if (doveSonoIo < doveDevoArrivare) {
            //orario
            //Esempio:
            //IO:340 ---> Arr:358  Ris=Orario
            //IO;350 ---> Arr: 275 ris Antiorario
            ris = 1;
          } else {
            ris = 2;
          }
        } else {
          //Caso in cui i gradi sono in quadranti differenti


          if (attualeQuad == 1 && arrivoQuad == 4) {
            //Sono nel 1 e devo andare nel 4  ---> Anti
            ris = 2;
          } else if (attualeQuad == 1 && arrivoQuad == 4) {
            //Sono nel 4 e devo andare nel 1 ---> Orario
            ris = 1;

          } else if (attualeQuad > arrivoQuad) { //Casi Semplici e generici
            ris = 2;
          } else {
            ris = 1;
          }
        }
        Serial.print("Devo girare a:");
        Serial.println(ris);
        //gradiToMove=abs(doveSonoIo-doveDevoArrivare);
        return ris;


      }





      int getRis1(int start, int finale) { //se valore positivo gira in senso ANTIORARIO, se negativo in senso ORARIO
        return start - finale;
      }

      int getRis2(int start, int finale) { //se valore positivo gira in senso ORARIO, se negativo in senso ANTIORARIO
        int ris = 0;
        if (start > finale) {
          start -= 360;
          ris = finale - start;
        }
        else {
          finale -= 360;
          ris = finale - start;
        }
        return ris;
      }

    };
