#pragma once
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "controller.h"
#include "accesspoint.h"

class WebServer
{
private:
	const int port;
	const char* ssid = "";
	const char* password = "";
	Controller controller;
	AsyncWebServer* server;
	boolean connect();
public:
	/**
	 * Constructor
	 */
	WebServer(const int port, Controller _controller);
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
