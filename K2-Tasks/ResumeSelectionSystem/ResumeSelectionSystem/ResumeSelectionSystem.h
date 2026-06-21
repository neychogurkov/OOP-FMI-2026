#pragma once
#include <vector>
#include "Requirement.h"
#include <memory>
#include "ResumePool.h"
#include <string>
#include "Resume.h"
#include <optional>
#include <utility>
class ResumeSelectionSystem {
	std::vector<std::unique_ptr<Requirement>> requirements;
	ResumePool resumePool;

	void free();
	void copyFrom(const ResumeSelectionSystem& other);

public:
	ResumeSelectionSystem() = default;

	ResumeSelectionSystem(const ResumeSelectionSystem& other);

	ResumeSelectionSystem& operator=(const ResumeSelectionSystem& other);

	void addRequirement(const std::pair<std::string, std::string>& req);
	std::vector<std::string> addResume(const Resume& resume);
	std::optional<Resume> findResume(const std::string& email) const;
	void removeResume(const std::string& email);
	const ResumePool& getPool() const;
};

