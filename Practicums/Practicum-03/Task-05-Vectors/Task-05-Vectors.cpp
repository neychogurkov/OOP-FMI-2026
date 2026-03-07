#include <iostream>
#include <fstream>

namespace constants {
	const int MAX_PATH_LENGTH = 100;
	const size_t MAX_VECTOR_COUNT = 50;
}

struct Vector {
	int x;
	int y;
	int z;
};

struct VectorSpace {
	Vector vectors[constants::MAX_VECTOR_COUNT];
	size_t vectorsCount;
};

Vector makeVector(int x, int y, int z) {
	return { x, y, z };
}

void addToVectorSpace(VectorSpace& vectorSpace, const Vector& vector) {
	if (vectorSpace.vectorsCount >= constants::MAX_VECTOR_COUNT) {
		std::cout << "Vector space is full. Cannot add more vectors.";
		return;
	}

	vectorSpace.vectors[vectorSpace.vectorsCount++] = vector;
}

void serializeVector(std::ofstream& ofs, const Vector& vector) {
	if (!ofs.is_open()) {
		std::cout << "Could not open file";
		return;
	}

	ofs << "<" << vector.x << ", " << vector.y << ", " << vector.z << "> ";
}

Vector deserializeVector(std::ifstream& ifs) {
	if (!ifs.is_open()) {
		std::cout << "Could not open file";
		return {};
	}

	Vector vector;

	ifs.ignore();
	ifs >> vector.x;
	ifs.ignore(2);
	ifs >> vector.y;
	ifs.ignore(2);
	ifs >> vector.z;
	ifs.ignore(2);

	return vector;
}

void serializeVectorSpace(const char* fileName, const VectorSpace& vectorSpace) {
	std::ofstream ofs(fileName);

	if (!ofs.is_open()) {
		std::cout << "Could not open file";
		return;
	}

	ofs << vectorSpace.vectorsCount << " ";

	for (size_t i = 0; i < vectorSpace.vectorsCount; i++) {
		serializeVector(ofs, vectorSpace.vectors[i]);
	}

	ofs.close();
}

VectorSpace deserializeVectorSpace(const char* fileName) {
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		std::cout << "Could not open file";
		return {};
	}

	VectorSpace vectorSpace;

	ifs >> vectorSpace.vectorsCount;

	if (vectorSpace.vectorsCount > constants::MAX_VECTOR_COUNT) {
		std::cout << "File contains too many vectors!";
		return {};
	}

	ifs.ignore();

	for (size_t i = 0; i < vectorSpace.vectorsCount; i++) {
		vectorSpace.vectors[i] = deserializeVector(ifs);
	}

	ifs.close();

	return vectorSpace;
}

int main()
{
	VectorSpace vectorSpace{};
	addToVectorSpace(vectorSpace, { 5, 2, -3 });
	addToVectorSpace(vectorSpace, { 2, 1, -1 });
	addToVectorSpace(vectorSpace, { -1, 7, 2 });
	addToVectorSpace(vectorSpace, { 4, 8, 3 });
	addToVectorSpace(vectorSpace, { -6, -1, 9 });
	addToVectorSpace(vectorSpace, { 8, -2, 7 });
	addToVectorSpace(vectorSpace, { 9, 0, -5 });
	addToVectorSpace(vectorSpace, { 12, 5, 0 });
	addToVectorSpace(vectorSpace, { 0, -1, 1 });
	addToVectorSpace(vectorSpace, { -3, 3, 0 });

	char path[constants::MAX_PATH_LENGTH];
	std::cin >> path;

	serializeVectorSpace(path, vectorSpace);

	VectorSpace vs = deserializeVectorSpace(path);
	std::cout << vs.vectorsCount << std::endl;

	for (size_t i = 0; i < vs.vectorsCount; i++) {
		std::cout << "<" << vs.vectors[i].x << ", " << vs.vectors[i].y << ", " << vs.vectors[i].z << "> " << std::endl;
	}
}