#pragma once
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "accesspoint.h"
#include "controllers/white_strip_controller.h"

class WebServer
{
private:
	const int port;
	const char* ssid = "";
	const char* password = "";
	AsyncWebServer* server;
	WhiteStripController white_strip_controller;
	boolean connect();
public:
	/**
	 * Constructor
	 */
	WebServer(const int port, WhiteStripController _white_strip_controller);
	/**
	 * Start the webserver
	 */
	void start();
	/**
	 * Stop the webserver
	 */
	void stop();
	/**
	 * Get the server host
	 */
	const String getHost();
};
