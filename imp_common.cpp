#include "imp_common.h"

SoftwareSerial impSerial(RX_PIN, TX_PIN);

void commonSetup() {
  pinMode(BUTTON, INPUT_PULLUP);
  impSerial.begin(19200);
  // printer init
  impSerial.printf("\x1B\x40");
}

void serialPrint(char* string) {
  impSerial.println(string);
}

void serialMode(byte printMode) {
  impSerial.printf("\x1B\x21");
  impSerial.print(printMode);
}

