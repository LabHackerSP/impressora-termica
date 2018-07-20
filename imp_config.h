#pragma once

#ifndef CONFIG_H_   /* Include guard */
#define CONFIG_H_

#include "imp_wifi.h"
#include "imp_common.h"
#include "spiffs_utils.h"

class impConfig {
  public:
    void setup(ESP8266WebServer *server);

  protected:
    ESP8266WebServer *ws;
    void GetSettings();
    void SetSettings();
    void SendPrint();
};

#endif // CONFIG_H_
