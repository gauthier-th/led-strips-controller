#pragma once
#include <string>
#include <map>

class Responses
{
private:
	static std::map<int, std::string> codes;
public:
	enum CODES { NO_ERROR=0, UNKNOWN_ENDPOINT=1 };

	static std::string getError(int code);
	static const char * getErrorMessage(int code);
};