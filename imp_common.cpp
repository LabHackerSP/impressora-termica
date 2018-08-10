#include "imp_common.h"

SoftwareSerial impSerial(RX_PIN, TX_PIN);
Adafruit_Thermal impPrinter(&impSerial, 16);

void commonSetup() {
  pinMode(BUTTON, INPUT_PULLUP);

  impSerial.begin(19200);
  impPrinter.begin();
}

