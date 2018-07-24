#include "imp_config.h"

void impConfig::setup(ESP8266WebServer *server) {
  ws = server;
  ws->on("/settings", HTTP_GET, std::bind(&impConfig::GetSettings, this));
  ws->on("/settings", HTTP_POST, std::bind(&impConfig::SetSettings, this));
  ws->on("/print", HTTP_POST, [this](){ ws->send(200); }, std::bind(&impConfig::SendPrint, this));
}

void impConfig::GetSettings() {
  String out = "";
  out += "<html><body><h1>Settings</h1>";
  out += "<form action=\"/settings\" method=\"post\">";

  out += "STA mode:<br>";
  out += "SSID: <input type=\"text\" name=\"sssid\" value=\"";
  out += loadDefault("/wifi/sta/ssid");
  out += "\"><br>";
  out += "Pass: <input type=\"text\" name=\"spass\" value=\"";
  out += loadDefault("/wifi/sta/pass");
  out += "\"><br>";

  out += "AP mode:<br>";
  out += "SSID: <input type=\"text\" name=\"assid\" value=\"";
  out += loadDefault("/wifi/ap/ssid");
  out += "\"><br>";
  out += "Pass: <input type=\"text\" name=\"apass\" value=\"";
  out += loadDefault("/wifi/ap/pass");
  out += "\"><br>";

  out += "<br>";
  out += "Endpoint: <input type=\"text\" name=\"endpoint\" value=\"";
  out += loadDefault("/endpoint");
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
    } else if(ar == "endpoint") {
      valid = true;
      fname = "/endpoint";
    }

    if(valid) {
      writeDefault(fname, ws->arg(i));
      out += ws->argName(i);
      out += ", ";
    }
  }
  
  ws->send(200, "text/plain", out);
}

//File fsUploadFile;

void impConfig::SendPrint() {
  HTTPUpload& upload = ws->upload();
  if(upload.status == UPLOAD_FILE_START){
    // start file upload
    //fsUploadFile = SPIFFS.open("/print", "w");
  } else if(upload.status == UPLOAD_FILE_WRITE){
    impSerial.write(upload.buf, upload.currentSize+1);
    /*if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);*/
  } else if(upload.status == UPLOAD_FILE_END){
    ws->send(200, "text/plain", "success!");
    /*if(fsUploadFile) {
      fsUploadFile.close();
      ws->send(200, "text/plain", loadDefault("/print"));
      // output file to printer
      fsUploadFile = SPIFFS.open("/print", "r");

      while(fsUploadFile.available()) {
        impSerial.write(fsUploadFile.read());
      }
      
      fsUploadFile.close();
    } else {
      ws->send(500, "text/plain", "500: couldn't create file");
    }*/
  }
}

