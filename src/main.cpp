#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include <ESP8266mDNS.h>
#include "store.h"
#include "webserver.h"
#include "controllers/white_strip_controller.h"
#include "infrared_receiver.h"

void loadLittleFS();

WhiteStripController white_strip_controller = WhiteStripController();
WebServer server = WebServer(80, white_strip_controller);
InfraredReceiver ir_receiver = InfraredReceiver(white_strip_controller);

void setup()
{
	Serial.begin(115200);
	while (!Serial) delay(50);
	Serial.println("Starting...");

	ESP.eraseConfig();
	WiFi.setAutoConnect(false);
	Store::init();
	loadLittleFS();

	ir_receiver.init();
	white_strip_controller.init();
	server.start();
}

void loop()
{
	ir_receiver.loop();
}

void loadLittleFS()
{
	if (!LittleFS.begin())
	{
		Serial.println("LittleFS error");
		return;
	}

	Dir dir = LittleFS.openDir("/");
	while (dir.next())
	{
		if (dir.fileSize())
		{
			File file = dir.openFile("r");
			file.close();
		}
	}
}