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
    bool rotDx;
    bool rotSx;
    int angoloStart;
    int gradiRot;
    bool particolare=false;

  public:
    Bussola()
    {
      rotDx = false;
      rotSx = false;
      gradiArrivo = 0;
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
      //if (direzione > getDegree())
      // portati a destra
      //else if (direzione < getDegree())
      // portati a sinistra


      
      //@Author Saccani
      //Controlla se i gradi effettivi sono compresi tra direzione+-5
      if(!versoCorretto(direzione)){
        //Ha sforato, quindi bisogna correggere l'andatura
        
        do{

          
          if(particolare){

            //Sono tra 0 e 5?
            if((direzione<=5 && direzione>=0) || (direzione>=355 && direzione<=360)){
              //Sono tra 180 e 360? Mi conviene fare orario
              if(getDegree()>=180){
                motori.spinOrario();
              }else{
                //Sono tra 0 e 179, faccio l'antiorario
                motori.spinAntiorario();
              }
            }
          }else{
            //Normale
            if(getDegree()>getSomma(direzione,5)){
            //Devo girare a sx
            motori.spinAntiorario();
            
          }else{
            //Devo girare a dx
           motori.spinOrario();
           
          }
          }

          
          

        }while(!versoCorretto(direzione));//Se sono ancora sforato, mi raddrizzo

        //Mi sono raddrizzato, quindi vado avanti
        motori.avanti();
      }

      
      particolare=false;

    }
    
    private boolean versoCorretto(int direzione){
      //@Author Saccani
      //Dice se sono nella direzione giusta
      int gradiEffettivi = getDegree();//350


      //Caso Particolare???  
      //Sono tra 0-5 o 355-360?
      if((direzione<=5 && direzione>=0) || (direzione>=355 && direzione<=360)){
        if(gradiEffettivi>=getSottrazione(direzione,5)){
          return true;
        }else{
          if(gradiEffettivi<=getSomma(direzione,5)){
            return true;
          }else{
            particolare=true;
            return false;
          }
        }
      }else if(gradiEffettivi<=getSomma(direzione,5) && gradiEffettivi>=getSottrazione(direzione,5)){ //Sono quindi in una situazione normale
          return true;
        }else{
          return false;
        }
        
    }

    private int correggi(int gradi){
      //@Author Saccani
      //Tipo: 350 ---> diventa 10
      return 360-gradi;
    }

    private int getSottrazione(int direzione, int diTot){
      //@Author Saccani
      int ris=direzione-diTot;

      if(ris<0){
        //Sono andato indietro di 0 gradi, trovo il corrispettivo 
        //Esempio:  direzione=0   diTot=5 ---> ris=-5   -->correggo in 355
        ris=360+ris;
      }
      return ris;
    }

    private int getSomma(int direzione, int diTot){
      //@Author Saccani
      int ris=direzione+diTot;

      if(ris>360){
        //Ho superato i 360, trovo il corrispettivo 
        //Esempio:  direzione=360   diTot=5 ---> ris=365   -->correggo in 5
        ris=ris-360;
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
      rotDx = true;
      motori.spinOrario();
    }
    void ruotaAntiorario()
    {
      gradiArrivo = (getDegree() - gradiP + 360) % 360;
      rotSx = true;
      motori.spinAntiorario();
    }
    bool stoRuotando()
    {
      if (rotDx || rotSx) return true;
      else return false;
    }
    void rotazioneFinita()
    {
      rotDx = false;
      rotSx = false;
      motori.avanti();
    }
    void checkRotation()
    {
      if (rotDx && ((getDegree() - angoloStart) >= gradiRot))
      {
        rotDx = false;
        motori.motorsOff();
      }
      else if (rotSx && ((getDegree() + gradiRot) >= angoloStart))
      {
        rotSx = false;
        motori.motorsOff();
      }
    }
    void testSpeed()
    {
      motori.spinOrario();
    }
	//@author mattia broch
	//metodo che dato un angolo iniziale e finale ritorna una stringa con ANTI o ORARIO per indicare la rotazione
	//e l'angolo alfa di rotazione
    string setDirezione(int start,int final){
	    int ris1=ris1(int start,int final);
	    int ris2=ris2(int start,int final);
	    
	    if(ris1<ris2){
		    if(ris1>0){
			    return "anti"+ris1;
		    }
	   	    else return "orario"+abs(ris1);
	    else{
		    if(ris2>0){
			    return "orario"+ris1;
		    }
	   	    else return "anti"+abs(ris2);		    
	    }
		    
    }
	
	int ris1(int start,int final){//se valore positivo gira in senso ANTIORARIO, se negativo in senso ORARIO
		return start-final;
	}
	
	int ris2(int start,int final){//se valore positivo gira in senso ORARIO, se negativo in senso ANTIORARIO
		int ris=0;
		if(start>fine){
			start-=360;
			ris=final-start;
		}
		else{
			final-=360;
			ris=final-start;
		}
			
	}
	
};
