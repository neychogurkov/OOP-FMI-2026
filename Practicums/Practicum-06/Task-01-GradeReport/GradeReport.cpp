#include "GradeReport.h"
#include <cstring>

void GradeReport::copyFrom(const GradeReport& other) {
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	gradesCount = other.gradesCount;
	grades = new unsigned[gradesCount];

	for (size_t i = 0; i < gradesCount; i++) {
		grades[i] = other.grades[i];
	}
}

void GradeReport::free() {
	delete[] name, grades;
	name = nullptr;
	grades = nullptr;
	gradesCount = 0;
}

GradeReport::GradeReport(unsigned* grades, size_t gradesCount, const char* name) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->gradesCount = gradesCount;
	this->grades = new unsigned[this->gradesCount];

	for (size_t i = 0; i < this->gradesCount; i++) {
		this->grades[i] = grades[i];
	}
}

GradeReport::GradeReport(const GradeReport& other) {
	copyFrom(other);
}

GradeReport& GradeReport::operator=(const GradeReport& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

GradeReport::~GradeReport() {
	free();
}

size_t GradeReport::getGradesCount() const {
	return gradesCount;
}

const char* GradeReport::getName() const {
	return name;
}

double GradeReport::getAverageGrade() const {
	unsigned sum = 0;

	for (size_t i = 0; i < gradesCount; i++) {
		sum += grades[i];
	}

	return (double)sum / gradesCount;
}

GradeReport GradeReport::merge(const GradeReport& lhs, const GradeReport& rhs) {
	GradeReport result;

	result.gradesCount = lhs.gradesCount + rhs.gradesCount;

	for (size_t i = 0; i < lhs.gradesCount; i++) {
		result.grades[i] = lhs.grades[i];
	}

	for (size_t i = 0; i < rhs.gradesCount; i++) {
		result.grades[lhs.gradesCount + i] = rhs.grades[i];
	}

	size_t leftLen = strlen(lhs.name);
	size_t rightLen = strlen(rhs.name);

	result.name = new char[leftLen + rightLen + 1];

	for (size_t i = 0; i < leftLen; i++) {
		result.name[i] = lhs.name[i];
	}

	for (size_t i = 0; i < rightLen; i++) {
		result.name[i + leftLen] = rhs.name[i];
	}

	result.name[leftLen + rightLen] = '\0';

	return result;
}
