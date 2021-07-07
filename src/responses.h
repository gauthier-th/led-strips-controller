#pragma once
#include <string>
#include <map>

class Responses
{
private:
	static std::map<int, const char*> codes;
public:
	enum CODES {
		NO_ERROR = 0,
		UNKNOWN_ENDPOINT = 1,
		INVALID_BODY = 2
	};

	static const char* getError(int code);
	static std::string getErrorMessage(int code);
};