#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "key_header.h"

const char* ssid     = "kk_2.4G";
const char* password = "88888888";

const uint16_t kIrLed = 16;
const int photoresistor_pin = A0;

ESP8266WebServer server(80);
IRsend irsend(kIrLed);


void handle_index() {
  server.send(200, "text/plain", "Here is ESP8266 WebServer!");
}
void handle_photoresistor() {
  int var = analogRead(photoresistor_pin);
  server.send(200, "text/plain", String(var));
}
void handle_ac_on() {
  irsend.sendRaw(key_on_rawData, 211, 38);
  server.send(200, "text/plain", "success");
}

void setup(void){
  irsend.begin();
  pinMode(photoresistor_pin, INPUT);
  Serial.begin(250000);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handle_index);
  server.on("/photoresistor", handle_photoresistor);
  server.on("/ac_on", handle_ac_on);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
