#pragma once
#include "Treasure.h";
#include "Constants.h";

class TreasureMap {
private:
	Treasure treasures[Constants::MAX_TREASURE_COUNT];
	size_t treasureCount;
	
	void sortBy(bool (*predicate)(const Treasure&, const Treasure&));

public:
	TreasureMap();

	void addTreasure(const char* name, int x, int y, int value);
	void removeTreasure(const char* name);
	Treasure findTreasure(int x, int y) const;
	Treasure getMostValuable() const;
	void sortByValue();
	void sortByDistance();
	void print() const;
	void saveToFile(const char* path) const;
	void readFromFile(const char* path);
};

