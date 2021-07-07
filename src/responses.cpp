#include "responses.h"
#include <Arduino.h>

std::map<int, const char*> Responses::codes = {
	{ 0, "null" },
	{ 1, "\"Unknown endpoint\"" }
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