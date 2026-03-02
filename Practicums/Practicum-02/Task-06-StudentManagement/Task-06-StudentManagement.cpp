#include <iostream>
#include <cstring>
#pragma warning(disable:4996)

namespace Constants {
	const int MAX_NAME_LENGTH = 32;
	const int MIN_FACULTY_NUMBER = 100000;
	const int MAX_FACULTY_NUMBER = 999999;
	const double MIN_GRADE = 2;
	const double MAX_GRADE = 6;
	const int MAX_STUDENTS_COUNT = 50;
}

enum class Major {
	DataAnalysis,
	Mathematics,
	AppliedMathematics,
	Statistics,
	Informatics,
	InformationSystems,
	ComputerScience,
	SoftwareEngineering
};

class Student {
private:
	char name[Constants::MAX_NAME_LENGTH + 1] = "";
	int facultyNumber = 0;
	double averageGrade = 0.0;
	Major major;

	const char* majorToString() const {
		switch (major) {
		case Major::DataAnalysis: return "Data Analysis";
		case Major::Mathematics: return "Mathematics";
		case Major::AppliedMathematics: return "Applied Mathematics";
		case Major::Statistics: return "Statistics";
		case Major::Informatics: return "Informatics";
		case Major::InformationSystems: return "Information Systems";
		case Major::SoftwareEngineering: return "Software Engineering";
		case Major::ComputerScience: return "Computer Science";
		default: return "Unknown";
		}
	}
public:
	const char* getName() const {
		return name;
	}

	int getFacultyNumber() const {
		return facultyNumber;
	}

	double getAverageGrade() const {
		return averageGrade;
	}

	Major getMajor() const {
		return major;
	}

	void setName(const char* name) {
		if (!name || strlen(name) > Constants::MAX_NAME_LENGTH) {
			std::cout << "Invalid name." << std::endl;
			return;
		}

		strncpy(this->name, name, Constants::MAX_NAME_LENGTH);
		this->name[Constants::MAX_NAME_LENGTH] = '\0';
	}

	void setFacultyNumber(int facultyNumber) {
		if (facultyNumber < Constants::MIN_FACULTY_NUMBER || facultyNumber > Constants::MAX_FACULTY_NUMBER) {
			std::cout << "Invalid faculty number." << std::endl;
			return;
		}

		this->facultyNumber = facultyNumber;
	}

	void setAverageGrade(double averageGrade) {
		if (averageGrade < Constants::MIN_GRADE || averageGrade > Constants::MAX_GRADE) {
			std::cout << "Invalid grade." << std::endl;
			return;
		}

		this->averageGrade = averageGrade;
	}

	void setMajor(Major major) {
		this->major = major;
	}

	void printStudent() const {
		std::cout << "Student " << name << " with faculty number " << facultyNumber << " and major " << majorToString() << " has an average grade of " << averageGrade << "." << std::endl;
	}
};

class Course {
private:
	Student students[Constants::MAX_STUDENTS_COUNT] = {};
	size_t studentsCount = 0;

public:
	const Student* getStudents() const {
		return students;
	}
	size_t getStudentsCount() const {
		return studentsCount;
	}

	void addStudent(const Student& student) {
		if (studentsCount >= Constants::MAX_STUDENTS_COUNT) {
			std::cout << "The course is full! The student could not be added." << std::endl;
			return;
		}

		students[studentsCount] = student;
		studentsCount++;
	}

	int findStudentByFacultyNumber(int facultyNumber) const {
		for (size_t i = 0; i < studentsCount; i++) {
			if (students[i].getFacultyNumber() == facultyNumber) {
				return i;
			}
		}

		return -1;
	}

	void removeStudent(int facultyNumber) {
		int index = findStudentByFacultyNumber(facultyNumber);

		if (index == -1) {
			std::cout << "Student with faculty number " << facultyNumber << " does not exist." << std::endl;
			return;
		}

		for (size_t i = index; i < studentsCount - 1; i++) {
			students[i] = students[i + 1];
		}

		students[studentsCount - 1] = {};

		studentsCount--;
	}

	void printStudents() const {
		for (size_t i = 0; i < studentsCount; i++) {
			students[i].printStudent();
		}
	}

	void filterStudents(bool(*predicate)(const Student&)) const {
		for (size_t i = 0; i < studentsCount; i++) {
			if (predicate(students[i])) {
				students[i].printStudent();
			}
		}
	}

	void sortStudents(bool(*predicate)(const Student&, const Student&)) {
		for (size_t i = 0; i < studentsCount - 1; i++) {
			size_t minIndex = i;

			for (size_t j = i + 1; j < studentsCount; j++) {
				if (predicate(students[j], students[minIndex])) {
					minIndex = j;
				}
			}

			if (minIndex != i) {
				Student temp = students[i];
				students[i] = students[minIndex];
				students[minIndex] = temp;
			}
		}
	}
};

Student createStudent(const char* name, int facultyNumber, double averageGrade, Major major) {
	Student student;
	student.setName(name);
	student.setFacultyNumber(facultyNumber);
	student.setAverageGrade(averageGrade);
	student.setMajor(major);

	return student;
}

void addStudentToCourse(Course& course, const Student& student) {
	course.addStudent(student);
}

void removeStudentFromCourse(Course& course, int facultyNumber) {
	course.removeStudent(facultyNumber);
}

void filterStudents(const Course& course, bool (*predicate)(const Student&)) {
	course.filterStudents(predicate);
}

void sortStudents(Course& course, bool(*predicate)(const Student&, const Student&)) {
	course.sortStudents(predicate);
}

int main() {
	Course course{};

	Student s1 = createStudent("Ivan", 123456, 5.5, Major::SoftwareEngineering);
	Student s2 = createStudent("Gosho", 1, 4, Major::Mathematics);
	Student s3 = createStudent("Petar", 753241, 7, Major::DataAnalysis);
	Student s4 = createStudent("Dimitar", 654279, 3.2, Major::AppliedMathematics);
	Student s5 = createStudent("Misho", 999999, 4.5, Major::ComputerScience);

	course.addStudent(s1);
	course.addStudent(s2);
	course.addStudent(s3);
	course.addStudent(s4);
	course.addStudent(s5);

	course.printStudents();
	std::cout << "------------------------------" << std::endl;

	course.filterStudents([](const Student& student) {return student.getMajor() == Major::SoftwareEngineering; });
	std::cout << "------------------------------" << std::endl;

	course.sortStudents([](const Student& student1, const Student& student2) {return student1.getAverageGrade() > student2.getAverageGrade(); });
	course.printStudents();
}