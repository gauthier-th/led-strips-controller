#include <Arduino.h>
#include "webserver.h"
#include "controller.h"

#ifndef STASSID
#define STASSID "****"
#define STAPSK  "****"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WebServer* server;
Controller* controller;

void setup() {
	controller = new Controller;
	server = new WebServer(80, ssid, password, controller);

	server->start();

	Serial.print("API working on ");
	Serial.println(server->getHost());
}

void loop() {
	server->loop();
}