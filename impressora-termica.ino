#include "imp_common.h"
#include "imp_wifi.h"
#include "spiffs_utils.h"

#define WDT_TIMEOUT 6000

void setup(void) {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

  spiffsSetup();
  commonSetup();
  setupWifi();
}

bool bounce = false;

HTTPClient http;

void loop(void) {
  handleWifi();
  // apenas OTA
  if(wifi_ap_mode) return;

  if(digitalRead(BUTTON) == LOW && !bounce) {
    bounce = true;
    
    //print from endpoint
    http.begin(loadDefault("/endpoint"));
    int httpCode = http.GET();
    //impSerial.printf("[HTTP] GET... code: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK) {
      // get length of document (is -1 when Server sends no Content-Length header)
      int len = http.getSize();
      
      // create buffer for read
      uint8_t buff;

      // get tcp stream
      WiFiClient * stream = http.getStreamPtr();

      // read all data from server
      while(http.connected()) {
        while(stream->available()) {
          // read a byte
          int c = stream->readBytes(&buff, 1);

          // write it to printer
          wdt_disable();
          impPrinter.writeBytes(buff);
          wdt_enable(WDT_TIMEOUT);
        }
      }
    } else {
      // http fail
      impSerial.print("falha HTTP: ");
      impSerial.println(http.errorToString(httpCode));
    }
    http.end();
  }

  if(digitalRead(BUTTON) == HIGH && bounce)
    bounce = false;
}
