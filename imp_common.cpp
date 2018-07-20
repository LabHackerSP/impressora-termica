#include "imp_common.h"

SoftwareSerial impSerial(RX_PIN, TX_PIN);

void commonSetup() {
  pinMode(BUTTON, INPUT_PULLUP);
  impSerial.begin(19200);
  // printer init
  delay(100);
  impSerial.write(0x1B);
  impSerial.write(0x40);
}

void serialPrint(char* s) { serialPrint(s, true); }
void serialPrint(char* string, bool lf) {
  impSerial.write(string);
  if(lf) impSerial.write(0x10);
}

void serialMode(byte printMode) {
  impSerial.write(0x1B);
  impSerial.write(0x21);
  impSerial.write(printMode);
}

