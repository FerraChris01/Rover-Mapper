#include <Wire.h>

#include "motors.h"

#ifndef Mecha_QMC5883
#include "MechaQMC5883.h"
#endif

class Bussola
{
  private:
    Motors motori;
    MechaQMC5883 qmc;
    int angoloStart;
    int gradiArrivo;
    int gradiRot;
    int gradiToMove=-1;
    bool rotazione = false;
    //bool particolare = false;

  public:
    Bussola()
    {
      Wire.begin();

      qmc.setMode(Mode_Continuous, ODR_200Hz, RNG_8G, OSR_512);

      motori = Motors();

      Serial.begin(9600);
      qmc.init();
    }
    int getDegree()
    {
      int x, y, z, heading;
      qmc.read(&x, &y, &z);

      heading = (int)(atan2(y, x) * 180 / 3.14) + 180;

      return heading;
    }


    void straighten(int direzione)
    {
      //@Author Saccani
      //Controlla se i gradi effettivi sono compresi tra direzione+-5
      if (!versoCorretto(direzione)) {
        //Ha sforato, quindi bisogna correggere l'andatura

          //Vedo dove devo andare per raddrizzarmi
          String ris = setDirezione(getDegree(), direzione);
        do {


          //Effettuo la correzione
          if (!(ris == "orario")) {
            Serial.println("Ruoto dx");
            if(gradiToMove<=30){
              motori.ruotaDx();
            }else{
              motori.spinOrario();
            }
            
          } else {
            Serial.println("Ruoto sx");
            if(gradiToMove<=30){
              motori.ruotaSx();
            }else{
              motori.spinAntiorario();
            }
            
          }


        } while (!versoCorretto(direzione)); //Se sono ancora sforato, mi raddrizzo

        //Mi sono raddrizzato, quindi vado avanti
        rotazione = false;
        motori.avanti();
      }


      //particolare = false;

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
    void ruotaOrario(int gradiP)
    {
      gradiArrivo = (getDegree() + gradiP) % 360;
      straighten(gradiArrivo);
      rotazione = true;

    }
    void ruotaAntiorario(int gradiP)
    {
      gradiArrivo = (getDegree() - gradiP + 360) % 360;
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
          gradiToMove=abs(ris1);
          return "anti";
        }
        else{
          gradiToMove=abs(ris1);
          return "orario";
        }
        
      }
        else {
          if (ris2 > 0) {
            gradiToMove=abs(ris2);
            return "anti";
          }
          else{
            gradiToMove=abs(ris2);
            return "orario";
          }
        }

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
