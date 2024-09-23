#include "webserver.h"
#include <cstring>
#include <ESP8266mDNS.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include "responses.h"
#include "store.h"
#include "config.h"
#include "utils/rewrite_url_param.h"

WebServer::WebServer(const int _port, WhiteStripController _white_strip_controller): port(_port), white_strip_controller(_white_strip_controller), server(new AsyncWebServer(_port))
{
  server->addRewrite(new RewriteUrlParam("/api/whiteStrip/{index}/setPower", "/api/whiteStrip/setPower?index={index}"));
  server->addRewrite(new RewriteUrlParam("/api/whiteStrip/{index}/setBrightness", "/api/whiteStrip/setBrightness?index={index}"));
}

void WebServer::start()
{
  if (!this->connect())
  {
    AccessPoint access_point = AccessPoint(server);
    access_point.init();
    return;
  }

  int controller_number = Store::readInt(Store::VALUES.CONTROLLER_NUMBER);
  if (controller_number > 1)
    MDNS.begin(MDNS_HOSTNAME + String(controller_number));
  else
    MDNS.begin(MDNS_HOSTNAME);

  this->server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
  });

  this->server->addHandler(new AsyncCallbackJsonWebHandler("/api/whiteStrip/setPower", [&](AsyncWebServerRequest *request, JsonVariant &json)
  {
    JsonObject json_obj = json.as<JsonObject>();
    if (json_obj.containsKey("value") && json_obj["value"].is<bool>())
    {
      white_strip_controller.set_power((bool) json_obj["value"]);
      request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
    }
    else
      request->send(400, "application/javascript", Responses::getErrorMessage(Responses::CODES::INVALID_BODY).c_str());
    white_strip_controller.update();
  }));
  this->server->addHandler(new AsyncCallbackJsonWebHandler("/api/whiteStrip/setBrightness", [&](AsyncWebServerRequest *request, JsonVariant &json)
  {
    JsonObject json_obj = json.as<JsonObject>();
    if (json_obj.containsKey("value") && json_obj["value"].is<int>())
    {
      white_strip_controller.set_brightness((int) json_obj["value"]);
      request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
    }
    else
      request->send(400, "application/javascript", Responses::getErrorMessage(Responses::CODES::INVALID_BODY).c_str());
    white_strip_controller.update();
  }));

  // this->server->addHandler(new AsyncCallbackJsonWebHandler("/api/addrStrip/setPower", [&](AsyncWebServerRequest *request, JsonVariant &json)
  // {
  //   JsonObject json_obj = json.as<JsonObject>();
  //   if (json_obj.containsKey("value") && json_obj["value"].is<bool>())
  //   {
  //     this->addr_strip_controller.set_power((bool) json_obj["value"]);
  //     request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
  //   }
  //   else
  //     request->send(400, "application/javascript", Responses::getErrorMessage(Responses::CODES::INVALID_BODY).c_str());
  // }));
  // this->server->addHandler(new AsyncCallbackJsonWebHandler("/api/addrStrip/setBrightness", [&](AsyncWebServerRequest *request, JsonVariant &json)
  // {
  //   JsonObject json_obj = json.as<JsonObject>();
  //   if (json_obj.containsKey("value") && json_obj["value"].is<int>())
  //   {
  //     this->addr_strip_controller.set_brightness((int) json_obj["value"]);
  //     request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
  //   }
  //   else
  //     request->send(400, "application/javascript", Responses::getErrorMessage(Responses::CODES::INVALID_BODY).c_str());
  // }));
  // this->server->addHandler(new AsyncCallbackJsonWebHandler("/api/addrStrip/setMode", [&](AsyncWebServerRequest *request, JsonVariant &json)
  // {
  //   JsonObject json_obj = json.as<JsonObject>();
  //   if (json_obj.containsKey("value") && json_obj["value"].is<int>())
  //   {
  //     this->addr_strip_controller.set_mode((int) json_obj["value"]);
  //     request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
  //   }
  //   else
  //     request->send(400, "application/javascript", Responses::getErrorMessage(Responses::CODES::INVALID_BODY).c_str());
  // }));
  // this->server->addHandler(new AsyncCallbackJsonWebHandler("/api/addrStrip/setSpeed", [&](AsyncWebServerRequest *request, JsonVariant &json)
  // {
  //   JsonObject json_obj = json.as<JsonObject>();
  //   if (json_obj.containsKey("value") && json_obj["value"].is<int>())
  //   {
  //     this->addr_strip_controller.set_speed((int) json_obj["value"]);
  //     request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
  //   }
  //   else
  //     request->send(400, "application/javascript", Responses::getErrorMessage(Responses::CODES::INVALID_BODY).c_str());
  // }));

  this->server->on("/api/reset", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    Store::writeString("", Store::VALUES.SSID);
    Store::writeString("", Store::VALUES.PASSWORD);
    Store::writeInt(0, Store::VALUES.CONTROLLER_NUMBER);
    request->send(200, "application/javascript", Responses::getErrorMessage(Responses::CODES::NO_ERROR).c_str());
    delay(200);
    ESP.restart();
  });

  this->server->onNotFound([](AsyncWebServerRequest *request)
  {
    request->send(404, "application/javascript", Responses::getErrorMessage(Responses::CODES::UNKNOWN_ENDPOINT).c_str());
  });

  this->server->begin();

  Serial.print("API working on ");
  Serial.println(this->getHost());
}

boolean WebServer::connect()
{
  String _ssid = Store::readString(Store::VALUES.SSID);
  String _password = Store::readString(Store::VALUES.PASSWORD);
  if (std::strcmp(_ssid.c_str(), "") == 0)
    return false;

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

const String WebServer::getHost()
{
  return WiFi.localIP().toString();
}
