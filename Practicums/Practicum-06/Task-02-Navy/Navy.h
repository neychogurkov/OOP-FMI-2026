#pragma once
#include "Ship.h"
class Navy {
private:
	char* country;
	Ship* ships;
	size_t shipsCount;

	void copyFrom(const Navy& other);
	void free();

public:
	Navy(const char* country);
	Navy(const Navy& other);
	Navy& operator=(const Navy& other);
	~Navy();

	int getShipsCount();
	void addShip(const Ship& ship);
	const Ship& getShip(size_t index);
	int compare(const Ship& other);
};

