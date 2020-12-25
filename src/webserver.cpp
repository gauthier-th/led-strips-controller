#include "webserver.h"

WebServer::WebServer(const int _port, const char* ssid, const char* password, Controller* _controller): port(_port), controller(_controller)
{
	this->server = new ESP8266WebServer(_port);
}

void WebServer::start()
{
	WiFi.mode(WIFI_STA);
	WiFi.begin(this->ssid, this->password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("WiFi Connect Failed! Rebooting...");
		delay(1000);
		ESP.restart();
	}
	ArduinoOTA.begin();

	this->server->on("/", [this]() {
		Serial.print("GET /");
		server->send(200, "application/json", "{\"code\":0,\"error\":null}");
	});
	this->server->begin();
}

void WebServer::loop()
{
	ArduinoOTA.handle();
	this->server->handleClient();
}

const String WebServer::getHost()
{
	return WiFi.localIP().toString();
}
