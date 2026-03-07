#include <iostream>
#include <fstream>

namespace constants {
	const int MAX_PATH_LENGTH = 100;
	const int BUFF_SIZE = 1024;
}

void printFile(std::ifstream& file) {
	if (!file.is_open()) {
		std::cout << "Could not open file.";
		return;
	}

	char buff[constants::BUFF_SIZE];

	while (file.getline(buff, constants::BUFF_SIZE)) {
		std::cout << buff << std::endl;
	}
}

int main() {
	char path[constants::MAX_PATH_LENGTH];
	std::cin >> path;

	std::ifstream file(path);
	printFile(file);
	file.close();
}
