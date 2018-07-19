#pragma once

#ifndef COMMON_H_   /* Include guard */
#define COMMON_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

const byte RX_PIN = 14;
const byte TX_PIN = 12;
const byte BUTTON = 13;

void commonSetup();

#endif // COMMON_H_
