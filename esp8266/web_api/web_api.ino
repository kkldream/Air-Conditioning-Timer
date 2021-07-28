#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "key_header.h"

const char* ssid     = "isip_2.4G";
const char* password = "isip7368";

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
void handle_send_key_fast() {
  irsend.sendRaw(KEY_FAST, 131, 38);
  server.send(200, "text/plain", "success");
}
void handle_send_key_mid() {
  irsend.sendRaw(KEY_MID, 131, 38);
  server.send(200, "text/plain", "success");
}
void handle_send_key_weak() {
  irsend.sendRaw(KEY_WEAK, 131, 38);
  server.send(200, "text/plain", "success");
}
void handle_send_key_sleep() {
  irsend.sendRaw(KEY_SLEEP, 131, 38);
  server.send(200, "text/plain", "success");
}
void handle_send_key_shutdown() {
  irsend.sendRaw(KEY_SHUTDOWN, 131, 38);
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
  server.on("/send_key_fast", handle_send_key_fast);
  server.on("/send_key_mid", handle_send_key_mid);
  server.on("/send_key_weak", handle_send_key_weak);
  server.on("/send_key_sleep", handle_send_key_sleep);
  server.on("/send_key_shutdown", handle_send_key_shutdown);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
