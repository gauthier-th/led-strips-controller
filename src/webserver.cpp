#include "webserver.h"
#include "responses.h"

WebServer::WebServer(const int _port, const char* _ssid, const char* _password, Controller* _controller):
		port(_port), ssid(_ssid), password(_password), controller(_controller), server(AsyncWebServer(_port))
{}

void notFound(AsyncWebServerRequest *request) {
	request->send(404, "application/javascript", Responses::getErrorMessage(Responses::CODES::UNKNOWN_ENDPOINT));
}

void WebServer::start() {
	WiFi.mode(WIFI_STA);
	WiFi.begin(this->ssid, this->password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("WiFi Failed!");
		return;
	}

	this->server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR));
	});

	this->server.onNotFound(notFound);

	this->server.begin();

	Serial.print("API working on ");
	Serial.println(this->getHost());
}

const String WebServer::getHost() {
	return WiFi.localIP().toString();
}
