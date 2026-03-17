#pragma once
#include "Constants.h"

class Treasure {
private:
	char name[Constants::MAX_NAME_LENGTH + 1];
	int x;
	int y;
	int value;
	
public:
	Treasure();
	Treasure(const char* name, int x, int y, int value);

	const char* getName() const;
	int getX() const;
	int getY() const;
	int getValue() const;

	void setName(const char* name);
	void setX(int x);
	void setY(int y);
	void setValue(int value);

	double getDistanceFromCenter() const;
	void print() const;
};

