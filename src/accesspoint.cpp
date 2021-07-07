#include "accesspoint.h"
#include "LittleFS.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "store.h"
#include "config.h"

AccessPoint::AccessPoint(AsyncWebServer* _server): server(_server)
{}

void AccessPoint::init() {
	if (std::strcmp(AP_PSK, "") == 0)
		WiFi.softAP(AP_SSID);
	else
		WiFi.softAP(AP_SSID, AP_PSK);

	IPAddress IP = WiFi.softAPIP();
	Serial.print("Access Point IP address: ");
	Serial.println(IP);

	this->server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, "/access_point.html", "text/html");
	});
	server->addHandler(new AsyncCallbackJsonWebHandler("/creditentials", [&](AsyncWebServerRequest *request, JsonVariant &json) {
		request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
		JsonObject jsonObj = json.as<JsonObject>();
		const char* ssid = jsonObj["ssid"];
		const char* password = jsonObj["password"];
		Serial.print("Receive SSID: ");
		Serial.println(ssid);
		Serial.print("And password: ");
		Serial.println(password);
		Store::writeString(ssid, Store::VALUES.SSID);
		Store::writeString(password, Store::VALUES.PASSWORD);
		Serial.println("Password successfully saved");
		delay(300);
		ESP.restart();
	}));

	this->server->onNotFound([](AsyncWebServerRequest *request) {
		request->send(404, "application/javascript", Responses::getErrorMessage(Responses::CODES::UNKNOWN_ENDPOINT).c_str());
	});

	this->server->begin();
}