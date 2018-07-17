#include "imp_common.h"
#include "imp_wifi.h"
#include "imp_serial.h"
#include "spiffs_utils.h"

void setup(void) {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

  spiffsSetup();
  commonSetup();
  setupWifi();
}

void loop(void) {
  handleWifi();
  //httpServer.handleClient();
}
