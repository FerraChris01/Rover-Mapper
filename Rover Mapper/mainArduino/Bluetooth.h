#include <SoftwareSerial.h>

#define BT_TX_PIN 12
#define BT_RX_PIN 13

class Bluetooth {

  private:
    SoftwareSerial bt = SoftwareSerial(BT_RX_PIN, BT_TX_PIN);
    String comandi[20];
    int numEl;

  public:
    Bluetooth() {
      pinMode(BT_RX_PIN, INPUT);
      pinMode(BT_TX_PIN, OUTPUT);
      numEl = 0;
      Serial.begin(9600);
      bt.begin(9600);
    }
    void sendData(int dDx, int dSx, int angolo, int velMotori)
    {
      bt.println(String(dDx) + ";" + String(dSx) + ";" + String(angolo) + ";" + String(velMotori));
      //Serial.println(String(dDx) + ";" + String(dSx) + ";" + String(angolo) + ";" + String(velMotori));
    }

    
    void readData() {
      while (bt.available() > 0)
        comandi[numEl++] = bt.readString();   
    }
    int getNumEl()
    {
      return numEl;
    }
    String popCommand()
    {
      return comandi[--numEl];
    }
    void resetArray()
    {
      numEl = 0;
    }
    void testSpeed(float speedP)
    {
      bt.println(speedP);
    }

    //Invia le distanze dei 3 sensori su seriale






};
