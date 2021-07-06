#include <tuple>
#include <Arduino.h>
#include <EEPROM.h>

constexpr struct ValuesStruct {
	std::tuple<int, int> SSID = std::make_tuple(0, 32);
	std::tuple<int, int> PASSWORD = std::make_tuple(32, 96);
} StoreValues;

class Store
{
public:
	static constexpr ValuesStruct VALUES = StoreValues;

	static void init();
	static void reset();

	static void writeChar(char value, std::tuple<int, int> address);
	static void writeInt(int value, std::tuple<int, int> address);
	static void writeString(String value, std::tuple<int, int> address);

	static char readChar(std::tuple<int, int> address);
	static int readInt(std::tuple<int, int> address);
	static String readString(std::tuple<int, int> address);
};