#pragma once

#ifndef SPIFFS_H_   /* Include guard */
#define SPIFFS_H_

#include "FS.h"

void spiffsSetup();
String loadDefault(const char* filename);
String loadDefault(const char* filename, String def);
void writeDefault(const char* filename, String def);

#endif // SPIFFS_H_
