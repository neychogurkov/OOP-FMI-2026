#include "ResumePool.h"
#include <string>
#include <optional>
#include "Resume.h"
#include <vector>
#include <algorithm>

std::optional<Resume> ResumePool::findByEmail(const std::string& email) const {
	return findFirst([&email](const Resume& r) { return r.getEmail() == email; });
}

std::vector<Resume> ResumePool::filterBySkill(const std::string& skill) const {
	return filter([&skill](const Resume& r)
		{
			return find(r.getSkills().begin(), r.getSkills().end(), skill) != r.getSkills().end();
		});
}

double ResumePool::averageSalary() const {
	if (isEmpty()) {
		return 0;
	}

	double sum = 0;

	for (const auto& el : data) {
		sum += el.getDesiredSalary();
	}

	return sum / size();
}
