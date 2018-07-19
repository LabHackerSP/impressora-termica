#include "imp_common.h"
#include "imp_wifi.h"
#include "spiffs_utils.h"

void setup(void) {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

  spiffsSetup();
  commonSetup();
  setupWifi();
}

bool bounce = false;

void loop(void) {
  handleWifi();

  if(digitalRead(BUTTON) == LOW && !bounce) {
    bounce = true;
    serialMode(MODE_FONT_B);
    serialPrint("hello");
    serialMode(MODE_FONT_B | MODE_REVERSE);
    serialPrint("hello");
    serialMode(MODE_FONT_B | MODE_DOUBLEWIDTH);
    serialPrint("hello");
  }

  if(digitalRead(BUTTON) == HIGH && bounce)
    bounce = false;
}
