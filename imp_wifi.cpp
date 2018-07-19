#include "imp_wifi.h"

const char* host = "impressora-termica";
ESP8266WebServer httpServer(80);
impConfig httpConfig;
ESP8266HTTPUpdateServer httpUpdater;

bool wifi_ap_mode = false;

void setupWifi() {
  char ip[64];
  String ssid;
  String pass;
  
  if(digitalRead(BUTTON) == LOW || !SPIFFS.exists("/wifi/sta/ssid")) {
    // AP mode
    wifi_ap_mode = true;
    ssid = loadDefault("/wifi/ap/ssid", "impressora");
    pass = loadDefault("/wifi/ap/pass", "senhasecreta");
    
    IPAddress local_IP(192,168,4,1);
    IPAddress gateway(192,168,4,1);
    IPAddress subnet(255,255,255,0);
    
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ssid.c_str(), pass.c_str());
    Serial.println("AP mode");
    Serial.printf("ssid: %s\npass: %s\n", ssid.c_str(), pass.c_str());
  } else {
    // STA mode
    ssid = loadDefault("/wifi/sta/ssid");
    pass = loadDefault("/wifi/sta/pass");
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());
    Serial.println("STA mode");
    Serial.printf("ssid: %s\npass: %s\n", ssid.c_str(), pass.c_str());
  }

  if(!wifi_ap_mode) {
    while(WiFi.waitForConnectResult() != WL_CONNECTED){
      WiFi.begin(ssid.c_str(), pass.c_str());
      Serial.println("WiFi STA failed, retrying.");
    }

    MDNS.begin(host);
    MDNS.addService("http", "tcp", 80);
    sprintf(ip, "%s.local", host);
  } else {
    String ipString = WiFi.softAPIP().toString();
    sprintf(ip, "%s", ipString.c_str());
  }
  
  httpUpdater.setup(&httpServer);
  httpConfig.setup(&httpServer);
  httpServer.begin();

  Serial.printf("HTTPUpdateServer ready! Open http://%s/update in your browser\n", ip);\
}

void handleWifi() {
  httpServer.handleClient();
}
