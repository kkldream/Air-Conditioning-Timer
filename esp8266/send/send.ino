#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "key_header.h"

const uint16_t kIrLed = 16;

IRsend irsend(kIrLed);

void setup() {
  irsend.begin();
  Serial.begin(250000);
}

void loop() {
  Serial.println("a rawData capture from IRrecvDumpV2");
  irsend.sendRaw(key_on_rawData, 211, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
}
