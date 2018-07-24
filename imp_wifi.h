#pragma once

#ifndef WIFI_H_   /* Include guard */
#define WIFI_H_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>

#include "spiffs_utils.h"
#include "imp_common.h"
#include "imp_config.h"

extern bool wifi_ap_mode;

void setupWifi();
void handleWifi();

#endif // WIFI_H_
