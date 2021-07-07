#pragma once
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "responses.h"

class AccessPoint
{
private:
	AsyncWebServer* server;
public:
	AccessPoint(AsyncWebServer* server);
	void init();
	void stop();
};