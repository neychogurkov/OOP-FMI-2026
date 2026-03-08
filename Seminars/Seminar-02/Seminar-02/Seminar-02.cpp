#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

namespace constants {
	const size_t BUFF_SIZE = 1024;
	const size_t MAX_NAME_LENGTH = 50;
	const size_t FACULTY_NUMBER_LENGTH = 10;
	const size_t MAX_STUDENTS_COUNT = 50;
}

struct Student {
	char name[constants::MAX_NAME_LENGTH + 1] = "";
	char facultyNumber[constants::FACULTY_NUMBER_LENGTH + 1] = "";
	double averageGrade = 0.0;

	void printStudent() const {
		std::cout << "Name: " << name << ", Faculty Number : " << facultyNumber << ", Grade : " << averageGrade << std::endl;
	}
};

struct Table {
	Student students[constants::MAX_STUDENTS_COUNT]{};
	size_t studentsCount = 0;

	void addStudent(const Student& student) {
		students[studentsCount++] = student;
	}

	int findStudentByFacultyNumber(const char* facultyNumber) const {
		for (size_t i = 0; i < studentsCount; i++) {
			if (strcmp(students[i].facultyNumber, facultyNumber) == 0) {
				return i;
			}
		}

		return -1;
	}

	void printStudentByFacultyNumber(const char* facultyNumber) const {
		int index = findStudentByFacultyNumber(facultyNumber);

		if (index == -1) {
			std::cout << "Student with faculty number " << facultyNumber << " does not exist." << std::endl;
			return;
		}

		students[index].printStudent();
	}

	void changeGradeByFacultyNumber(const char* facultyNumber, double averageGrade) {
		int index = findStudentByFacultyNumber(facultyNumber);

		if (index == -1) {
			std::cout << "Student with faculty number " << facultyNumber << " does not exist." << std::endl;
			return;
		}

		students[index].averageGrade = averageGrade;
		std::cout << "Grade updated successfully." << std::endl;
	}
};

bool serialize(const Table& table, std::ofstream& file) {
	if (!file.is_open()) {
		std::cout << "Could not open file.";
		return false;
	}

	file << "| Name | Faculty Number | Grade |\n|------|----------------|-------|\n";

	for (size_t i = 0; i < table.studentsCount; i++) {
		file << "| " << table.students[i].name << " | " << table.students[i].facultyNumber << " | " << table.students[i].averageGrade << " |" << std::endl;
	}

	return true;
}

void trim(char* str) {
	if (!str) {
		return;
	}

	int length = strlen(str);

	for (size_t i = 0; i < length - 2; i++) {
		str[i] = str[i + 1];
	}

	str[length - 2] = '\0';
}

Table deserialize(std::ifstream& file) {
	Table table{};

	if (!file.is_open()) {
		std::cout << "Could not open file.";
		return table;
	}

	char buff[constants::BUFF_SIZE];

	file.getline(buff, constants::BUFF_SIZE);
	file.getline(buff, constants::BUFF_SIZE);

	Student student{};

	while (file.ignore(constants::BUFF_SIZE, '|') && !file.eof()) {
		file.getline(student.name, constants::MAX_NAME_LENGTH + 3, '|');

		trim(student.name);
		file.getline(student.facultyNumber, constants::FACULTY_NUMBER_LENGTH + 3, '|');
		trim(student.facultyNumber);
		file >> student.averageGrade;
		file.ignore(constants::BUFF_SIZE, '\n');

		table.addStudent(student);
	}

	return table;
}

int main() {
	std::cout << "Open file:\n>";
	char inputPath[constants::BUFF_SIZE];
	std::cin.getline(inputPath, constants::BUFF_SIZE);

	std::ifstream ifs(inputPath);
	Table table = deserialize(ifs);

	std::cout << "File successfully opened!" << std::endl;

	while (true) {
		std::cout << ">";
		char command[constants::BUFF_SIZE];
		std::cin.getline(command, constants::BUFF_SIZE, ' ');

		if (strcmp(command, "print") == 0) {
			char facultyNumber[constants::BUFF_SIZE];
			std::cin.getline(facultyNumber, constants::BUFF_SIZE);

			table.printStudentByFacultyNumber(facultyNumber);
		}
		else if (strcmp(command, "update_grade") == 0) {
			char facultyNumber[constants::BUFF_SIZE];
			std::cin.getline(facultyNumber, constants::BUFF_SIZE, ' ');
			char buff[constants::BUFF_SIZE];
			std::cin.getline(buff, constants::BUFF_SIZE);
			double grade = std::atof(buff);

			table.changeGradeByFacultyNumber(facultyNumber, grade);
		}
		else if (strcmp(command, "save") == 0) {
			char path[constants::BUFF_SIZE];
			std::cin.getline(path, constants::BUFF_SIZE);

			std::ofstream ofs(path);
			if (serialize(table, ofs)) {
				std::cout << "File " << path << " was saved successfully!" << std::endl;
				break;
			}
		}
	}
}