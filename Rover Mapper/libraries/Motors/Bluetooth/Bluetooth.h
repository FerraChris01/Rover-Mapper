#include "SoftwareSerial.h"

#define BT_TX_PIN 12		//da cambiare
#define BT_RX_PIN 13

class Bluetooth {

private:
	SoftwareSerial bt = SoftwareSerial(BT_RX_PIN, BT_TX_PIN);

public:
	Bluetooth() {
		pinMode(BT_RX_PIN, INPUT);
		pinMode(BT_TX_PIN, OUTPUT);		
		Serial.begin(9600);
		bt.begin(9600);
	}

	void sendData(float dDx, float dSx, int angolo) 
	{
			bt.print(String(dDx) + ";" + String(dSx) + ";" + String(angolo));
	}	

	void read() {
		while (bt.available() > 0) {
			Serial.println(bt.read());
		}
	}

	//Invia le distanze dei 3 sensori su seriale






};