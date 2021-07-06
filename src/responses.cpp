#include "responses.h"

std::map<int, std::string> Responses::codes = {
	{ 0, "null" },
	{ 1, "\"Unknown endpoint\"" }
};

std::string Responses::getError(int code) {
	if (Responses::codes.find(code) != Responses::codes.end())
		return Responses::codes[code];
	else
		return "\"\"";
}

const char * Responses::getErrorMessage(int code) {
	std::string message = "{\"code\":" + std::to_string(code) + ",\"error\":" + Responses::getError(code) + "}";
	return message.c_str();
}