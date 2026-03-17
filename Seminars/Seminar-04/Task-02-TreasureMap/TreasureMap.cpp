#include "TreasureMap.h"
#include <cmath>
#include <cstring>
#include <fstream>

void TreasureMap::sortBy(bool(*predicate)(const Treasure&, const Treasure&)) {
	for (size_t i = 0; i < treasureCount - 1; i++) {
		size_t minIndex = i;

		for (size_t j = i + 1; j < treasureCount; j++) {
			if (predicate(treasures[j], treasures[minIndex])) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			std::swap(treasures[i], treasures[minIndex]);
		}
	}
}

TreasureMap::TreasureMap() :treasureCount(0) {
}

void TreasureMap::addTreasure(const char* name, int x, int y, int value) {
	if (treasureCount >= Constants::MAX_TREASURE_COUNT) {
		return;
	}

	treasures[treasureCount++] = Treasure(name, x, y, value);
}

void TreasureMap::removeTreasure(const char* name) {
	for (size_t i = 0; i < treasureCount; i++) {
		if (strcmp(treasures[i].getName(), name) == 0) {
			for (size_t j = i; j < treasureCount - 1; j++) {
				treasures[j] = treasures[j + 1];
			}

			treasureCount--;
			i--;
		}
	}
}

Treasure TreasureMap::findTreasure(int x, int y) const {
	for (size_t i = 0; i < treasureCount; i++) {
		if (treasures[i].getX() == x && treasures[i].getY() == y) {
			return treasures[i];
		}
	}

	return {};
}

Treasure TreasureMap::getMostValuable() const {
	if (treasureCount == 0) {
		return {};
	}

	size_t index = 0;

	for (size_t i = 1; i < treasureCount; i++) {
		if (treasures[i].getValue() > treasures[index].getValue()) {
			index = i;
		}
	}

	return treasures[index];
}

void TreasureMap::sortByValue() {
	sortBy([](const Treasure& t1, const Treasure& t2) { return t1.getValue() < t2.getValue(); });
}

void TreasureMap::sortByDistance() {
	sortBy([](const Treasure& t1, const Treasure& t2) { return t1.getDistanceFromCenter() < t2.getDistanceFromCenter(); });
}

void TreasureMap::print() const {
	for (size_t i = 0; i < treasureCount; i++) {
		treasures[i].print();
	}
}

void TreasureMap::saveToFile(const char* path) const {
	if (!path) {
		return;
	}

	std::ofstream file(path, std::ios::binary);

	if (!file.is_open()) {
		return;
	}

	file.write((const char*)&treasureCount, sizeof(size_t));
	file.write((const char*)treasures, sizeof(Treasure) * treasureCount);

	file.close();
}

void TreasureMap::readFromFile(const char* path) {
	if (!path) {
		return;
	}

	std::ifstream file(path, std::ios::binary);

	if (!file.is_open()) {
		return;
	}

	file.read((char*)&treasureCount, sizeof(size_t));

	if (treasureCount > Constants::MAX_TREASURE_COUNT) {
		treasureCount = 0;
		return;
	}

	file.read((char*)treasures, sizeof(Treasure) * treasureCount);

	file.close();
}
