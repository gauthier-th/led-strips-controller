#include "responses.h"
#include <Arduino.h>

std::map<int, const char*> Responses::codes = {
	{ Responses::CODES::NO_ERROR, "null" },
	{ Responses::CODES::UNKNOWN_ENDPOINT, "\"Unknown endpoint\"" },
	{ Responses::CODES::INVALID_BODY, "\"Invalid body\"" }
};

const char* Responses::getError(int code) {
	if (Responses::codes.find(code) != Responses::codes.end())
		return Responses::codes[code];
	else
		return "\"\"";
}

std::string Responses::getErrorMessage(int code) {
	std::string message = "{\"code\":" + std::to_string(code) + ",\"error\":" + Responses::getError(code) + "}";
	return message;
}