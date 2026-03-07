#include <iostream>
#include <fstream>

namespace constants {
	const int MAX_PATH_LENGTH = 100;
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


void saveHalfFile(const char* path) {
	std::ifstream ifs(path);

	if (!ifs.is_open()) {
		std::cout << "Could not open file.";
		return;
	}

	size_t halfSize = getFileSize(ifs) / 2;

	char* buff = new char[halfSize];
	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	ifs.read(buff, halfSize);

	ifs.close();

	std::ofstream ofs(path);

	if (!ofs.is_open()) {
		std::cout << "Could not open file.";
		return;
	}

	ofs.write(buff, halfSize);
	ofs.close();

	delete[] buff;
}

int main() {
	char path[constants::MAX_PATH_LENGTH];
	std::cin >> path;

	saveHalfFile(path);
}