#include <stdlib.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include "controller.h"

class WebServer
{
private:
	const int port;
	const char* ssid;
	const char* password;
	ESP8266WebServer* server;
	Controller* controller;
public:
	/**
	 * Constructor
	 */
	WebServer(const int port, const char* ssid, const char* password, Controller* _controller);
	/**
	 * Start the webserver
	 */
	void start();
	/**
	 * Loop function of the webserver
	 */
	void loop();
	/**
	 * Stop the webserver
	 */
	void stop();
	/**
	 * Get the server host
	 */
	const String getHost();
};
