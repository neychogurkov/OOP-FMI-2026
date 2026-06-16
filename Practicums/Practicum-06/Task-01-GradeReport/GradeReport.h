#pragma once
class GradeReport {
private:
	unsigned* grades;
	size_t gradesCount;
	char* name;

	void copyFrom(const GradeReport& other);
	void free();

public:
	GradeReport() = default;
	GradeReport(unsigned* grades, size_t gradesCount, const char* name);
	GradeReport(const GradeReport& other);
	GradeReport& operator=(const GradeReport& other);
	~GradeReport();

	size_t getGradesCount() const;
	const char* getName() const;
	double getAverageGrade() const;

	static GradeReport merge(const GradeReport& lhs, const GradeReport& rhs);
};

