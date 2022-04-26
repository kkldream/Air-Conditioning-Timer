#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "key_header.h"

const char* ssid     = "E408A1";
const char* password = "73427342";

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
void handle_send_key_17() {
  irsend.sendRaw(KEY_17, sizeof(KEY_17)/sizeof(KEY_17[0]), 38);
  server.send(200, "text/plain", "success");
}
void handle_send_key_20() {
  irsend.sendRaw(KEY_20, sizeof(KEY_20)/sizeof(KEY_20[0]), 38);
  server.send(200, "text/plain", "success");
}
void handle_send_key_22() {
  irsend.sendRaw(KEY_22, sizeof(KEY_22)/sizeof(KEY_22[0]), 38);
  server.send(200, "text/plain", "success");
}
void handle_send_key_24() {
  irsend.sendRaw(KEY_24, sizeof(KEY_24)/sizeof(KEY_24[0]), 38);
  server.send(200, "text/plain", "success");
}
void handle_send_key_26() {
  irsend.sendRaw(KEY_26, sizeof(KEY_26)/sizeof(KEY_26[0]), 38);
  server.send(200, "text/plain", "success");
}
void handle_send_key_shutdown() {
  irsend.sendRaw(KEY_SHUTDOWN, sizeof(KEY_SHUTDOWN)/sizeof(KEY_SHUTDOWN[0]), 38);
  server.send(200, "text/plain", "success");
}

void setup(void){
  pinMode(LED_BUILTIN, OUTPUT);
  irsend.begin();
  pinMode(photoresistor_pin, INPUT);
  Serial.begin(250000);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
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
  server.on("/send_key_17", handle_send_key_17);
  server.on("/send_key_20", handle_send_key_20);
  server.on("/send_key_22", handle_send_key_22);
  server.on("/send_key_24", handle_send_key_24);
  server.on("/send_key_26", handle_send_key_26);
  server.on("/send_key_shutdown", handle_send_key_shutdown);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
