#include "webserver.h"

WebServer::WebServer(const int _port, const char* _ssid, const char* _password, Controller* _controller): port(_port), ssid(_ssid), password(_password), controller(_controller), server(AsyncWebServer(_port))
{}

void notFound(AsyncWebServerRequest *request) {
	request->send(404, "text/plain", "Page not found");
}

void WebServer::start() {
	WiFi.mode(WIFI_STA);
	WiFi.begin(this->ssid, this->password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.printf("WiFi Failed!\n");
		return;
	}

	this->server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(200, "text/plain", "Hello, world");
	});

	this->server.onNotFound(notFound);

	this->server.begin();

	Serial.print("API working on ");
	Serial.println(this->getHost());
}

const String WebServer::getHost() {
	return WiFi.localIP().toString();
}
