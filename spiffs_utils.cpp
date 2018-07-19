#include "spiffs_utils.h"

void spiffsSetup() {
  if(SPIFFS.begin() == false)
    Serial.println("Falha ao montar SPIFFS!");
}

/* loadDefault sem default, retorna string vazia caso não carregue */
String loadDefault(const char* filename) {
  return loadDefault(filename, "");
}

/* helper para carregar uma variável do SPIFFS, caso não exista retorna um default */
String loadDefault(const char* filename, String def) {
  File f;
  f = SPIFFS.open(filename, "r");
  if(f) {
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

/* helper para gravar default em SPIFFS */
void writeDefault(const char* filename, String def) {
  File f;
  f = SPIFFS.open(filename, "w");
  f.print(def);
  f.close();
}

