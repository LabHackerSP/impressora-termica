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
      uint8_t buff[128] = { 0 };

      // get tcp stream
      WiFiClient * stream = http.getStreamPtr();

      // read all data from server
      while(http.connected() && (len > 0 || len == -1)) {
        // get available data size
        size_t size = stream->available();

        if(size) {
          // read up to 128 byte
          int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));

          // write it to printer
          impSerial.write(buff, c);

          if(len > 0)
            len -= c;
        }
        delay(1);
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
