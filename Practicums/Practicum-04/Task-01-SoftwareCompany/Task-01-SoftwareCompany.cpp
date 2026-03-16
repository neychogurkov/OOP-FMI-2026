#include <iostream>
#include <cstring>
#pragma warning(disable:4996)

namespace Constants {
	const size_t MAX_NAME_LENGTH = 32;
	const unsigned MIN_AGE = 18;
	const unsigned MIN_SALARY = 2500;
	const unsigned MAX_SALARY = 5000;
	const char DEFAULT_NAME[] = "Unknown";
	const size_t LANGUAGES_COUNT = 5;

	const size_t MAX_PROGRAMMER_COUNT = 50;
}

enum class Language {
	Cpp,
	Python,
	Java,
	CSharp,
	JavaScript
};

const char* languageToString(Language language) {
	switch (language) {
		case Language::Cpp:
			return "C++";
		case Language::Python:
			return "Python";
		case Language::Java:
			return "Java";
		case Language::CSharp:
			return "C#";
		case Language::JavaScript:
			return "JavaScript";
		default:
			return "Unknown";
	}
}

class Programmer {
private:
	char name[Constants::MAX_NAME_LENGTH + 1];
	unsigned age;
	unsigned salary;
	bool languages[Constants::LANGUAGES_COUNT]{};

	bool isValidName(const char* name) const {
		return name && strlen(name) <= Constants::MAX_NAME_LENGTH;
	}

	bool isValidAge(unsigned age) const {
		return age >= Constants::MIN_AGE;
	}

	bool isValidSalary(unsigned salary) const {
		return salary >= Constants::MIN_SALARY && salary <= Constants::MAX_SALARY;
	}

	bool isValidLanguage(Language language) const {
		return (int)language >= 0 && (int)language < Constants::LANGUAGES_COUNT;
	}

	void setName(const char* name) {
		if (!isValidName(name)) {
			strcpy(this->name, Constants::DEFAULT_NAME);
			return;
		}

		strcpy(this->name, name);
	}

	void setAge(unsigned age) {
		if (!isValidAge(age)) {
			this->age = Constants::MIN_AGE;
			return;
		}

		this->age = age;
	}

	void printLanguages() const {
		for (size_t i = 0; i < Constants::LANGUAGES_COUNT; i++) {
			Language language = (Language)i;

			if (knowsLanguage(language)) {
				std::cout << languageToString(language) << " ";
			}
		}
	}
public:
	Programmer() {
		setName(Constants::DEFAULT_NAME);
		setAge(Constants::MIN_AGE);
		setSalary(Constants::MIN_SALARY);
	}

	Programmer(const char* name, unsigned age, unsigned salary) {
		setName(name);
		setAge(age);
		setSalary(salary);
	}


	void setSalary(unsigned salary) {
		if (!isValidSalary(salary)) {
			this->salary = Constants::MIN_SALARY;
			return;
		}

		this->salary = salary;
	}

	const char* getName() const {
		return name;
	}

	unsigned getAge() const {
		return age;
	}

	unsigned getSalary() const {
		return salary;
	}

	void learnLanguage(Language language) {
		if (!isValidLanguage(language)) {
			return;
		}

		languages[(int)language] = true;
	}

	bool knowsLanguage(Language language) const {
		if (!isValidLanguage(language)) {
			return false;
		}

		return languages[(int)language];
	}

	void print() const {
		std::cout << name << " | " << age << " | " << salary << " | ";
		printLanguages();
		std::cout << std::endl;
	}
};

class SoftwareCompany {
private:
	Programmer programmers[Constants::MAX_PROGRAMMER_COUNT];
	size_t programmersCount;

	double calculateAverage(double(*getter)(const Programmer&)) const {
		if (programmersCount == 0) {
			return 0;
		}

		double sum = 0;

		for (size_t i = 0; i < programmersCount; i++) {
			sum += getter(programmers[i]);
		}

		return (double)sum / programmersCount;
	}

	void sortProgrammers(bool(*predicate)(const Programmer&, const Programmer&)) {
		for (size_t i = 0; i < programmersCount - 1; i++) {
			size_t minIndex = i;

			for (size_t j = i + 1; j < programmersCount; j++) {
				if (predicate(programmers[j], programmers[minIndex])) {
					minIndex = j;
				}
			}

			if (minIndex != i) {
				Programmer temp = programmers[i];
				programmers[i] = programmers[minIndex];
				programmers[minIndex] = temp;
			}
		}
	}
public:
	SoftwareCompany() :programmersCount(0) {
	}

	void addProgrammer(const Programmer& programmer) {
		if (programmersCount >= Constants::MAX_PROGRAMMER_COUNT) {
			return;
		}

		programmers[programmersCount++] = programmer;
	}

	int getProgrammersCount() const {
		return programmersCount;
	}

	void print() const {
		for (size_t i = 0; i < programmersCount; i++) {
			programmers[i].print();
		}
	}

	void filterProgrammersByLanguage(Language language) const {
		for (size_t i = 0; i < programmersCount; i++) {
			if (programmers[i].knowsLanguage(language)) {
				programmers[i].print();
			}
		}
	}

	double calculateAverageSalary() const {
		return calculateAverage([](const Programmer& pr) {return (double)pr.getSalary(); });
	}

	double calculateAverageAge() const {
		return calculateAverage([](const Programmer& pr) {return (double)pr.getAge(); });
	}

	bool changeSalary(size_t programmerIndex, double (*formula)(double)) {
		if (programmerIndex >= programmersCount) {
			return false;
		}

		Programmer& programmer = programmers[programmerIndex];
		programmer.setSalary(formula(programmer.getSalary()));

		return true;
	}

	void sortBySalary() {
		sortProgrammers([](const Programmer& p1, const Programmer& p2) {return p1.getSalary() < p2.getSalary(); });
	}

	void sortByAge() {
		sortProgrammers([](const Programmer& p1, const Programmer& p2) {return p1.getAge() < p2.getAge(); });
	}
};

int main() {
	SoftwareCompany company;

	Programmer p1("Ivan Ivanov", 25, 3000);
	p1.learnLanguage(Language::Cpp);
	p1.learnLanguage(Language::Python);

	Programmer p2("Maria Petrova", 21, 4500);
	p2.learnLanguage(Language::JavaScript);
	p2.learnLanguage(Language::Java);

	Programmer p3("Georgi Kolev", 30, 2800);
	p3.learnLanguage(Language::CSharp);
	p3.learnLanguage(Language::Python);

	company.addProgrammer(p1);
	company.addProgrammer(p2);
	company.addProgrammer(p3);

	std::cout << "\n--- All Programmers ---\n";
	company.print();

	std::cout << "\nAverage Salary: " << company.calculateAverageSalary() << " BGN";
	std::cout << "\nAverage Age: " << company.calculateAverageAge() << " years" << std::endl;

	std::cout << "\n--- Sorted by Salary ---\n";
	company.sortBySalary();
	company.print();

	company.changeSalary(0, [](double s) { return s * 1.10; });

	std::cout << "\n--- After Bonus (10%) ---\n";
	company.print();

	std::cout << "\n--- Sorted by Salary ---\n";
	company.sortBySalary();
	company.print();

	std::cout << "\n--- Sorted by Age ---\n";
	company.sortByAge();
	company.print();

	std::cout << "\n--- Python Developers ---\n";
	company.filterProgrammersByLanguage(Language::Python);
}