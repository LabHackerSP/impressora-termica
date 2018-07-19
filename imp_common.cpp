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

void serialPrint(char* string) {
  impSerial.println(string);
}

void serialMode(byte printMode) {
  impSerial.write(0x1B);
  impSerial.write(0x21);
  impSerial.write(printMode);
}

