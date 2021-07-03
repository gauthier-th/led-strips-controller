#include <Arduino.h>
// #include <SPIFFS.h>
#include "webserver.h"
#include "controller.h"

#include "config.h"

const char* ssid = STASSID;
const char* password = STAPSK;

WebServer* server;
Controller* controller;

void setup() {
	Serial.begin(115200);

	controller = new Controller;
	server = new WebServer(80, ssid, password, controller);

	server->start();
}

void loop() {
	
}