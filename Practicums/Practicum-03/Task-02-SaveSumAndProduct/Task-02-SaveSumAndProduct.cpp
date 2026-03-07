#include <iostream>
#include <fstream>

namespace constants {
	const int MAX_PATH_LENGTH = 100;
}

void saveSumAndProduct(const char* inputPath, const char* outputPath) {
	std::ifstream inputFile(inputPath);

	if (!inputFile.is_open()) {
		std::cout << "Could not open input file.";
		return;
	}

	int a, b;
	inputFile >> a >> b;
	inputFile.close();

	std::ofstream outputFile(outputPath);

	if (!outputFile.is_open()) {
		std::cout << "Could not open output file.";
		return;
	}

	outputFile << a + b << " " << a * b;

	outputFile.close();
}

int main() {
	char inputPath[constants::MAX_PATH_LENGTH], outputPath[constants::MAX_PATH_LENGTH];
	std::cin >> inputPath >> outputPath;

	saveSumAndProduct(inputPath, outputPath);
}