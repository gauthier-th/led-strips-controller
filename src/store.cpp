#include "store.h"

void Store::init() {
	EEPROM.begin(512);
}

void Store::reset() {
	for (int i = 0; i < 512; i++) {
		EEPROM.write(i, 0);
	}
	EEPROM.commit();
}

void Store::writeChar(char value, std::tuple<int, int> address) {
	EEPROM.write(std::get<0>(address), value);
	EEPROM.commit();
}
void Store::writeInt(int value, std::tuple<int, int> address) {
	EEPROM.write(std::get<0>(address), value);
	EEPROM.commit();
}
void Store::writeString(String value, std::tuple<int, int> address) {
	for (unsigned int i = 0; i < value.length(); i++) {
		EEPROM.write(std::get<0>(address) + i, value[i]);
	}
	for (int i = value.length() + std::get<0>(address); i < std::get<1>(address); i++) {
		EEPROM.write(i, 0);
	}
	EEPROM.commit();
}

char Store::readChar(std::tuple<int, int> address) {
	return char(EEPROM.read(std::get<0>(address)));
}
int Store::readInt(std::tuple<int, int> address) {
	return int(EEPROM.read(std::get<0>(address)));
}
String Store::readString(std::tuple<int, int> address) {
	String text = "";
	for (int i = 0; i < std::get<1>(address); i++) {
		uint8_t value = EEPROM.read(std::get<0>(address) + i);
		if (value == 0)
			break;
		else
			text = text + char(value);
	}
	return text;
}