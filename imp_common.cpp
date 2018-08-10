#include "imp_common.h"

SoftwareSerial impSerial(RX_PIN, TX_PIN);
Adafruit_Thermal impPrinter(&impSerial, DTR_PIN);

void commonSetup() {
  pinMode(BUTTON, INPUT_PULLUP);

  impSerial.begin(19200);
  impPrinter.begin();
}

