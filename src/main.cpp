#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include "webserver.h"
#include "controller.h"
#include "store.h"

void loadLittleFS();

Controller controller = Controller();
WebServer server = WebServer(80, controller);

void setup() {
	Serial.begin(115200);
	while (!Serial) {}
	Serial.println("Starting...");

	ESP.eraseConfig();
	WiFi.mode(WIFI_AP_STA);
	WiFi.setAutoConnect(false);
	Store::init();
	loadLittleFS();

	controller.init();
	server.start();
}

void loop() {
	
}

void loadLittleFS() {
	if (!LittleFS.begin()) {
		Serial.println("LittleFS error");
		return;
	}

	Dir dir = LittleFS.openDir("/");
	while (dir.next()) {
		if (dir.fileSize()) {
			File file = dir.openFile("r");
			file.close();
		}
	}
}