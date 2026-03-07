#include <iostream>
#include <fstream>

namespace constants {
	const int MAX_PATH_LENGTH = 100;
	const int BUFF_SIZE = 1024;
}

size_t getFileSize(std::ifstream& file) {
	if (!file.is_open()) {
		return 0;
	}

	size_t curr = file.tellg();
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(curr);

	return size;
}

void wc(std::ifstream& file) {
	if (!file.is_open()) {
		std::cout << "Could not open file.";
		return;
	}

	size_t bytesCount = getFileSize(file);
	size_t rowsCount = 0;
	size_t wordsCount = 0;
	
	char ch;
	bool inWord = false;

	while (file.get(ch)) {
		if (ch == '\n') {
			rowsCount++;
		}

		if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') {
			inWord = false;
		}
		else
		{
			if (!inWord) {
				wordsCount++;
				inWord = true;
			}
		}
	}

	rowsCount++;

	std::cout << rowsCount << " " << wordsCount << " " << bytesCount << " ";
}

int main(){
	char path[constants::MAX_PATH_LENGTH];
	std::cin >> path;
	std::ifstream file(path);
	wc(file);

	file.close();
}