#pragma once

#ifndef COMMON_H_   /* Include guard */
#define COMMON_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

const byte RX_PIN = 14;
const byte TX_PIN = 12;
const byte BUTTON = 13;

const byte MODE_FONT_B       = 1;
const byte MODE_REVERSE      = 2;
const byte MODE_UPSIDEDOWN   = 4;
const byte MODE_EMPHASIZED   = 8;
const byte MODE_DOUBLEHEIGHT = 16;
const byte MODE_DOUBLEWIDTH  = 32;
const byte MODE_DELETELINE   = 64;

extern SoftwareSerial impSerial;

void commonSetup();

void serialPrint(char*);
void serialPrint(char*, bool);
void serialMode(byte);

#endif // COMMON_H_
