#include "ultrasuoni.h"
#define BT_TX_PIN 1
#define BT_RX_PIN 0

class Bluetooth {

	SoftwareSerial bt;
	Ultrasuoni ul;

	Bluetooth() {
		pinMode(BT_RX_PIN, INPUT);
		pinMode(BT_TX_PIN, OUTPUT);
		Serial.begin(9600);
		bt.begin(9600);
		SoftwareSerial(BT_RX_PIN, BT_TX_PIN);
		ul = new Ultrasuoni();
	}

	void readS() {
		// se ci sono dati sul buffer della Serial
		while (Serial.available() > 0) {
			//mandali al modulo bluetooth
			bt.print(Serial.read());
		}
	}

	void readB() {
		while (bt.available() > 0) {
			//mostrali nel Serial Monitor
			Serial.println(bt.read());
		}
	}

	//Invia le distanze dei 3 sensori su seriale

	void inviaDistanze(Ultrasuoni ul,float angolo) {
		ul.calcolaDistanze();
		ul.sendDxSx();	

	}





};