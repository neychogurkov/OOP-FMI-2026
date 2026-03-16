#include <iostream>
#include <cstring>
#pragma warning(disable:4996)

namespace Constants {
	const int MAX_MAKE_LENGTH = 100;
	const char DEFAULT_MAKE[] = "Unknown";
	const int ENGINE_TYPES_COUNT = 3;
	const size_t MAX_CARS_COUNT = 1000;
}

enum class EngineType {
	GASOLINE,
	DIESEL,
	ELECTRICITY
};

class Car {
private:
	char make[Constants::MAX_MAKE_LENGTH + 1];
	char model[Constants::MAX_MAKE_LENGTH + 1];
	EngineType engineType;
	bool isUsed;
	unsigned mileage;
	double price;

	bool isValidMake(const char* make) const {
		return make && strlen(make) <= Constants::MAX_MAKE_LENGTH;
	}

	bool isValidModel(const char* model) const {
		return model && strlen(model) <= Constants::MAX_MAKE_LENGTH;
	}

	bool isValidEngineType(EngineType engineType) const {
		return (int)engineType >= 0 && (int)engineType < Constants::ENGINE_TYPES_COUNT;
	}

	bool isValidPrice(double price) const {
		return price > 0;
	}

	const char* engineTypeToString(EngineType engineType) const {
		switch (engineType) {
			case EngineType::GASOLINE:
				return "Gasoline";
			case EngineType::DIESEL:
				return "Diesel";
			case EngineType::ELECTRICITY:
				return "Electricity";
			default:
				return "Unknown";
		}
	}

public:
	Car() {
		setMake(Constants::DEFAULT_MAKE);
		setModel(Constants::DEFAULT_MAKE);
		engineType = EngineType::GASOLINE;
		isUsed = false;
		mileage = 0;
		price = 0;
	}

	Car(const char* make, const char* model, EngineType engineType, double price) {
		setMake(make);
		setModel(model);
		setEngineType(engineType);
		setPrice(price);

		isUsed = false;
		mileage = 0;
	}

	void setMake(const char* make) {
		if (!isValidMake(make)) {
			strcpy(this->make, Constants::DEFAULT_MAKE);
			return;
		}

		strcpy(this->make, make);
	}

	void setModel(const char* model) {
		if (!isValidModel(model)) {
			strcpy(this->model, Constants::DEFAULT_MAKE);
			return;
		}

		strcpy(this->model, model);
	}

	void setEngineType(EngineType engineType) {
		if (!isValidEngineType(engineType)) {
			return;
		}

		this->engineType = engineType;
	}

	void setPrice(double price) {
		if (!isValidPrice(price)) {
			this->price = 0;
			return;
		}

		this->price = price;
	}

	const char* getMake() const {
		return make;
	}

	const char* getModel() const {
		return model;
	}

	EngineType getEngineType() const {
		return engineType;
	}

	double getPrice() const {
		return price;
	}

	void print() const {
		std::cout << make << " | " << model << " | " << engineTypeToString(engineType) << " | " << price << " | " << (isUsed ? "Used" : "New") << " | " << mileage << std::endl;
	}

	void drive(unsigned kilometers) {
		if (kilometers > 0) {
			isUsed = true;
			mileage += kilometers;
			double newPrice = price - price * 0.001 * kilometers;
			price = newPrice > 0 ? newPrice : 0;
		}
	}
};

class Dealership {
private:
	Car cars[Constants::MAX_CARS_COUNT];
	size_t carsCount;

public:
	Dealership(const Car* cars, size_t count) :carsCount(0) {
		if (count > Constants::MAX_CARS_COUNT) {
			count = Constants::MAX_CARS_COUNT;
		}

		for (size_t i = 0; i < count; i++) {
			this->cars[i] = cars[i];
		}

		carsCount = count;
	}

	Dealership(const Car* cars, size_t count, EngineType engineType) :carsCount(0) {
		if (count > Constants::MAX_CARS_COUNT) {
			count = Constants::MAX_CARS_COUNT;
		}

		for (size_t i = 0; i < count; i++) {
			if (cars[i].getEngineType() == engineType) {
				this->cars[this->carsCount++] = cars[i];
			}
		}
	}

	Dealership(const Car* cars, size_t count, const char* model) :carsCount(0) {
		if (count > Constants::MAX_CARS_COUNT) {
			count = Constants::MAX_CARS_COUNT;
		}

		for (size_t i = 0; i < count; i++) {
			if (strcmp(cars[i].getModel(), model) == 0) {
				this->cars[this->carsCount++] = cars[i];
			}
		}
	}

	size_t getCarsCount() const {
		return carsCount;
	}

	bool addCar(const Car& car) {
		if (carsCount >= Constants::MAX_CARS_COUNT) {
			return false;
		}

		cars[carsCount++] = car;

		return true;
	}

	void removeCar(const char* make, const char* model) {
		for (size_t i = 0; i < carsCount; i++) {
			if (strcmp(cars[i].getMake(), make) == 0 && strcmp(cars[i].getModel(), model) == 0) {
				if (i == carsCount - 1) {
					cars[i] = {};
				}
				else {
					for (size_t j = i; j < carsCount - 1; j++) {
						cars[j] = cars[j + 1];
					}
				}

				carsCount--;
				break;
			}
		}
	}

	void testDrive() {
		for (size_t i = 0; i < carsCount; i++) {
			cars[i].drive(1);
		}
	}

	void printCarsByModel(const char* model) const {
		for (size_t i = 0; i < carsCount; i++) {
			if (strcmp(cars[i].getModel(), model) == 0) {
				cars[i].print();
			}
		}
	}

	Car findMostExpensiveCar() const {
		if (carsCount == 0) {
			return Car();
		}

		size_t index = 0;

		for (size_t i = 1; i < carsCount; i++) {
			if (cars[i].getPrice() > cars[index].getPrice()) {
				index = i;
			}
		}

		return cars[index];
	}

	double getAveragePrice(const Car& car) const {
		double sum = 0;
		int count = 0;

		for (size_t i = 0; i < carsCount; i++) {
			if (strcmp(cars[i].getMake(), car.getMake()) == 0) {
				sum += cars[i].getPrice();
				count++;
			}
		}

		return count == 0 ? 0.0 : sum / count;
	}
};

int main() {

	Car cars[] = {
		Car("BMW", "X5", EngineType::DIESEL, 90000),
		Car("Tesla", "Model3", EngineType::ELECTRICITY, 70000),
		Car("Audi", "A4", EngineType::GASOLINE, 60000),
		Car("BMW", "M3", EngineType::GASOLINE, 120000),
		Car("Tesla", "ModelS", EngineType::ELECTRICITY, 110000),
		Car("Audi", "A4", EngineType::DIESEL, 65000)
	};

	size_t carsCount = sizeof(cars) / sizeof(cars[0]);

	std::cout << "----- Dealership with all cars -----\n";
	Dealership d1(cars, carsCount);

	std::cout << "Cars count: " << d1.getCarsCount() << std::endl;

	std::cout << "\n----- Adding a new car -----\n";
	Car newCar("Mercedes", "C200", EngineType::DIESEL, 75000);
	d1.addCar(newCar);

	std::cout << "Cars count after adding: " << d1.getCarsCount() << std::endl;

	std::cout << "\n----- Removing BMW M3 -----\n";
	d1.removeCar("BMW", "M3");

	std::cout << "Cars count after removal: " << d1.getCarsCount() << std::endl;

	std::cout << "\n----- Test drive all cars (1 km) -----\n";
	d1.testDrive();

	std::cout << "\n----- Cars with model A4 -----\n";
	d1.printCarsByModel("A4");

	std::cout << "\n----- Most expensive car -----\n";
	Car mostExpensive = d1.findMostExpensiveCar();
	mostExpensive.print();

	std::cout << "\n----- Average price of BMW cars -----\n";
	Car exampleBMW("BMW", "Any", EngineType::GASOLINE, 0);
	std::cout << d1.getAveragePrice(exampleBMW) << std::endl;

	std::cout << "\n----- Dealership with only ELECTRIC cars -----\n";
	Dealership electricCars(cars, carsCount, EngineType::ELECTRICITY);
	std::cout << "Electric cars count: " << electricCars.getCarsCount() << std::endl;
	electricCars.printCarsByModel("Model3");
	electricCars.printCarsByModel("ModelS");

	std::cout << "\n----- Dealership with only model A4 -----\n";
	Dealership modelA4(cars, carsCount, "A4");
	std::cout << "A4 cars count: " << modelA4.getCarsCount() << std::endl;
	modelA4.printCarsByModel("A4");

	std::cout << "\n----- Driving a single car manually -----\n";
	Car testCar("Toyota", "Corolla", EngineType::GASOLINE, 30000);
	testCar.print();

	testCar.drive(100);
	std::cout << "After driving 100 km:\n";
	testCar.print();

	return 0;
}