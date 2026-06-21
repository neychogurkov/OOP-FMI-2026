#include "Resume.h"

Resume::Resume(const std::string& firstName, const std::string& lastName, const std::string& email, unsigned age, unsigned yearsOfExperience, const std::vector<std::string>& skills, double desiredSalary) :firstName(firstName), lastName(lastName), email(email), age(age), yearsOfExperience(yearsOfExperience), skills(skills), desiredSalary(desiredSalary){
}

const std::string& Resume::getFirstName() const {
	return firstName;
}

const std::string& Resume::getLastName() const {
	return lastName;
}

const std::string& Resume::getEmail() const {
	return email;
}

unsigned Resume::getAge() const {
	return age;
}

unsigned Resume::getYearsOfExperience() const {
	return yearsOfExperience;
}

const std::vector<std::string>& Resume::getSkills() const {
	return skills;
}

double Resume::getDesiredSalary() const {
	return desiredSalary;
}
