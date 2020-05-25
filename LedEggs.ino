#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <WiFiManager.h>

ESP8266WebServer server(80);

char led_status = 1;

void set_status(char s) {
  led_status = s;
  digitalWrite(0, led_status);
  digitalWrite(2, led_status);
}

void handle_toggle() {
  set_status(!led_status);
  server.send(200, "text/plain", led_status ? "ON" : "OFF");
}

void handle_turn_on() {
  set_status(1);
  server.send(200, "text/plain", "ON");
}

void handle_turn_off() {
  set_status(0);  
  server.send(200, "text/plain", "OFF");
}

void setup() {
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Starting up...");

  WiFiManager wifi_manager;

  digitalWrite(0, HIGH);
  digitalWrite(2, HIGH);

  wifi_manager.autoConnect("LedEggs");

  server.on("/toggle", handle_toggle);
  server.on("/on", handle_turn_on);
  server.on("/off", handle_turn_off);

  server.begin();
  
  Serial.println("Ready");
}

void loop() {
  Serial.println(".");
  server.handleClient();
}
