#include <iostream>
#include <fstream>

namespace constants {
	const size_t MAX_NAME_LENGTH = 24;
	const size_t MAX_FINES_COUNT = 20;
	const char FILE_PATH[] = "cars.bin";
}

enum class Make {
	BMW,
	MercedesBenz,
	Audi,
	Toyota,
	Honda,
	Porsche,
	VW,
	Lamborghini,
	Chevrolette
};

struct Car {
	Make make;
	char owner[constants::MAX_NAME_LENGTH + 1];
	double averageSpeed;
	double fines[constants::MAX_FINES_COUNT];
	size_t finesCount;
};

const char* makeToString(Make make) {
	switch (make) {
	case Make::BMW: return "BMW";
	case Make::MercedesBenz: return "Mercedes-Benz";
	case Make::Audi: return "Audi";
	case Make::Toyota: return "Toyota";
	case Make::Honda: return "Honda";
	case Make::Porsche: return "Porsche";
	case Make::VW: return "Volkswagen";
	case Make::Lamborghini: return "Lamborghini";
	case Make::Chevrolette: return "Chevrolette";
	default: return "Unknown";
	}
}

double calculateTotalFines(const Car& car) {
	double sum = 0;

	for (size_t i = 0; i < car.finesCount; i++)
	{
		sum += car.fines[i];
	}

	return sum;
}

void addFine(Car& car, double fineAmount) {
	if (car.finesCount >= constants::MAX_FINES_COUNT) {
		std::cout << "The limit of fines is reached! Could not add a new fine.";
		return;
	}

	car.fines[car.finesCount++] = fineAmount;
}

void printCar(const Car& car) {
	std::cout << "Make: " << makeToString(car.make)
		<< ", Owner: " << car.owner
		<< ", Average speed: " << car.averageSpeed
		<< ", Fines count: " << car.finesCount
		<< ", Fines amount: " << calculateTotalFines(car) << std::endl;
}

void serializeCar(std::ofstream& ofs, const Car& car) {
	if (!ofs.is_open()) {
		std::cout << "Could not open file";
		return;
	}

	ofs.write((const char*)&car, sizeof(Car));
}

Car deserializeCar(std::ifstream& ifs) {
	if (!ifs.is_open() || ifs.eof()) {
		std::cout << "Could not open file";
		return {};
	}

	Car car;
	ifs.read((char*)&car, sizeof(Car));

	return car;
}

size_t getFileSize(std::fstream& file) {
	if (!file.is_open()) {
		return 0;
	}

	size_t curr = file.tellg();
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(curr);

	return size;
}

void sortCars(Car* cars, size_t carsCount, bool (*predicate)(const Car&, const Car&)) {
	for (size_t i = 0; i < carsCount; i++) {
		size_t minIndex = i;

		for (size_t j = i + 1; j < carsCount; j++) {
			if (predicate(cars[j], cars[minIndex])) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			Car temp = cars[i];
			cars[i] = cars[minIndex];
			cars[minIndex] = temp;
		}
	}
}

void sortFile(std::fstream& file) {
	if (!file.is_open()) {
		std::cout << "Could not open file";
		return;
	}

	size_t fileSize = getFileSize(file);
	size_t carsCount = fileSize / sizeof(Car);
	Car* cars = new Car[carsCount];

	file.clear();
	file.seekg(0, std::ios::beg);
	file.read((char*)cars, fileSize);

	sortCars(cars, carsCount, [](const Car& car1, const Car& car2) {return car1.averageSpeed < car2.averageSpeed; });

	file.clear();
	file.seekp(0, std::ios::beg);
	file.write((const char*)cars, fileSize);

	delete[] cars;
}

int main() {
	Car cars[] = {
		{ Make::BMW, "Ivan Ivanov", 70, {20, 50, 100, 20, 10}, 5 },
		{ Make::MercedesBenz, "Georgi Georgiev", 20, {25, 100, 500}, 3 },
		{ Make::Toyota, "Petar Petrov", 40, {}, 0 }
	};

	for (const auto& car : cars) {
		std::cout << calculateTotalFines(car) << std::endl;
	}

	addFine(cars[2], 1000);
	std::cout << calculateTotalFines(cars[2]) << std::endl;

	std::ofstream ofs(constants::FILE_PATH, std::ios::binary);

	for (const auto& car : cars) {
		serializeCar(ofs, car);
	}

	ofs.close();

	std::ifstream ifs(constants::FILE_PATH, std::ios::binary);
	
	for (auto& car : cars) {
		car = deserializeCar(ifs);
	}

	ifs.close();

	for (const auto& car : cars) {
		printCar(car);
	}

	std::fstream fs(constants::FILE_PATH, std::ios::binary | std::ios::in | std::ios::out);

	sortFile(fs);

	fs.close();

	std::ifstream ifs2(constants::FILE_PATH, std::ios::binary);

	for (auto& car : cars) {
		car = deserializeCar(ifs2);
	}

	ifs2.close();

	for (const auto& car : cars) {
		printCar(car);
	}
}