#include <bluetooth.h>

Bluetooth bt = Bluetooth();

void setup() {
  Serial.begin(9600);

}

void loop() {
  bt.sendData(1.0, 2.0, 3);
  delay(1000);
}
