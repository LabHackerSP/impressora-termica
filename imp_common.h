
#pragma once

#ifndef COMMON_H_   /* Include guard */
#define COMMON_H_

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>

const byte RX_PIN  = 14;
const byte TX_PIN  = 12;
const byte DTR_PIN = 16;
const byte BUTTON  = 13;

extern SoftwareSerial impSerial;
extern Adafruit_Thermal impPrinter;

void commonSetup();

void serialPrint(char*);
void serialPrint(char*, bool);
void serialMode(byte);

#endif // COMMON_H_
