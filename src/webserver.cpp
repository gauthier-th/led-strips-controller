#include "webserver.h"
#include <cstring>
#include "responses.h"
#include "store.h"
#include "config.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"

WebServer::WebServer(const int _port, Controller _controller): port(_port), controller(_controller), server(new AsyncWebServer(_port))
{
}

void WebServer::start() {
	if (!this->connect()) {
		AccessPoint accessPoint = AccessPoint(server);
		accessPoint.init();
		return;
	}

	this->server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
	});
	server->addHandler(new AsyncCallbackJsonWebHandler("/setLight", [&](AsyncWebServerRequest *request, JsonVariant &json) {
		JsonObject jsonObj = json.as<JsonObject>();
		if (jsonObj.containsKey("pin") && jsonObj.containsKey("ratio") && jsonObj["pin"].is<int>() && jsonObj["ratio"].is<int>()) {
			this->controller.setLight((int) jsonObj["pin"], (int) jsonObj["ratio"]);
			request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
		}
		else
			request->send(400, "application/javascript", Responses::getErrorMessage(Responses::CODES::INVALID_BODY).c_str());
	}));

	this->server->onNotFound([](AsyncWebServerRequest *request) {
		request->send(404, "application/javascript", Responses::getErrorMessage(Responses::CODES::UNKNOWN_ENDPOINT).c_str());
	});

	this->server->begin();

	Serial.print("API working on ");
	Serial.println(this->getHost());
}

boolean WebServer::connect() {
	String _ssid = Store::readString(Store::VALUES.SSID);
	String _password = Store::readString(Store::VALUES.PASSWORD);
	this->ssid = _ssid.c_str();
	this->password = _password.c_str();

	Serial.print("Try to connect to ");
	Serial.print(this->ssid);
	Serial.print(" with password ");
	Serial.println(this->password);

	WiFi.hostname(STA_HOSTNAME);
	if (std::strcmp(this->ssid, "") == 0)
		return false;

	WiFi.begin(this->ssid, this->password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED)
		Serial.println("WiFi connection failed! (attempt 1)");
	else
		return true;
	delay(2000);

	WiFi.begin(this->ssid, this->password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED)
		Serial.println("WiFi connection failed! (attempt 2)");
	else
		return true;
	delay(2000);

	WiFi.begin(this->ssid, this->password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED)
		Serial.println("WiFi connection failed! (attempt 3)");
	else
		return true;
	delay(2000);

	return false;
}

const String WebServer::getHost() {
	return WiFi.localIP().toString();
}
