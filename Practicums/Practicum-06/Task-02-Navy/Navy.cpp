#include "Navy.h"
#include <cstring>

void Navy::copyFrom(const Navy& other) {

}

void Navy::free() {
	delete[] country, ships;
	country = nullptr;
	ships = nullptr;
	shipsCount = 0;
}

Navy::Navy(const char* country) :shipsCount(0) {
	this->country = new char[strlen(country) + 1];
	strcpy(this->country, country);
}

Navy::Navy(const Navy& other) {
	copyFrom(other);
}

Navy& Navy::operator=(const Navy& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
}

Navy::~Navy() {
	free();
}

int Navy::getShipsCount() {
	return shipsCount;
}

void Navy::addShip(const Ship& ship) {
	ships[shipsCount++] = ship;
}

const Ship& Navy::getShip(size_t index) {
	return ships[index];
}

int Navy::compare(const Navy& other) {
	int gunsCount = 0;

	for (size_t i = 0; i < shipsCount; i++) {

	}
}
