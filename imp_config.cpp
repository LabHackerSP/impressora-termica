#include "imp_config.h"

void impConfig::setup(ESP8266WebServer *server) {
  ws = server;
  ws->on("/settings", HTTP_GET, std::bind(&impConfig::GetSettings, this));
  ws->on("/settings", HTTP_POST, std::bind(&impConfig::SetSettings, this));
}

void impConfig::GetSettings() {
  String out = "";
  out += "<html><body><h1>Settings</h1>";
  out += "<form action=\"/settings\" method=\"post\">";

  out += "STA mode:<br>";
  out += "SSID: <input type=\"text\" name=\"sssid\" value=\"";
  out += loadDefault("/wifi/sta/ssid");
  out += "\"><br>";\
  out += "Pass: <input type=\"text\" name=\"spass\" value=\"";
  out += loadDefault("/wifi/sta/pass");
  out += "\"><br>";

  out += "AP mode:<br>";
  out += "SSID: <input type=\"text\" name=\"assid\" value=\"";
  out += loadDefault("/wifi/ap/ssid");
  out += "\"><br>";\
  out += "Pass: <input type=\"text\" name=\"apass\" value=\"";
  out += loadDefault("/wifi/ap/pass");
  out += "\"><br>";
  
  out += "<input type=\"submit\" value=\"Submit\"></form>";
  out += "</body></html>";
  
  ws->send(200, "text/html", out);
}

void impConfig::SetSettings() {
  String out = "Updated: ";
  
  for (int i = 0; i < ws->args(); i++) {
    bool valid = false;
    const char* fname;
    String ar = ws->argName(i);
    if(ar == "sssid") {
      valid = true;
      fname = "/wifi/sta/ssid";
    } else if(ar == "spass") {
      valid = true;
      fname = "/wifi/sta/pass";
    } else if(ar == "assid") {
      valid = true;
      fname = "/wifi/ap/ssid";
    } else if(ar == "apass") {
      valid = true;
      fname = "/wifi/ap/pass";
    }

    if(valid) {
      writeDefault(fname, ws->arg(i));
      out += ws->argName(i);
      out += ", ";
    }
  }
  
  ws->send(200, "text/plain", out);
}
