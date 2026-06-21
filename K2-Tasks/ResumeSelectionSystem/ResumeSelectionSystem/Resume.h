#pragma once
#include <string>
#include <vector>
class Resume {
	std::string firstName;
	std::string lastName;
	std::string email;
	unsigned age;
	unsigned yearsOfExperience;
	std::vector<std::string> skills;
	double desiredSalary;

public:
	Resume(const std::string& firstName, const std::string& lastName, const std::string& email, unsigned age, unsigned yearsOfExperience, const std::vector<std::string>& skills, double desiredSalary);

	const std::string& getFirstName() const;
	const std::string& getLastName() const;
	const std::string& getEmail () const;
	unsigned getAge() const;
	unsigned getYearsOfExperience() const;
	const std::vector<std::string>& getSkills() const;
	double getDesiredSalary() const;
};

