#include "spiffs_utils.h"

void spiffsSetup() {
  if(SPIFFS.begin() == false)
    Serial.println("Falha ao montar SPIFFS!");
}

String loadDefault(const char* filename) {
  return loadDefault(filename, "");
}

String loadDefault(const char* filename, String def) {
  File f;
  if(SPIFFS.exists(filename)) {
    f = SPIFFS.open(filename, "r");
    String out = f.readString();
    f.close();
    return out;
  } else {
    if(def.length() >= 0) {
      f = SPIFFS.open(filename, "w");
      f.print(def);
      f.close();
    }
    return def;
  }
}

void writeDefault(const char* filename, String def) {
  File f;
  f = SPIFFS.open(filename, "w");
  f.print(def);
  f.close();
}

