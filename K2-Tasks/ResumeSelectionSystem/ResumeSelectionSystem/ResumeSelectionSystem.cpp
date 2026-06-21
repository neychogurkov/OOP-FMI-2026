#include "ResumeSelectionSystem.h"
#include "RequirementFactory.h"
#include <optional>
#include <string>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <vector>
#include "Resume.h"

void ResumeSelectionSystem::free() {
    requirements.clear();
}

void ResumeSelectionSystem::copyFrom(const ResumeSelectionSystem& other) {
    this->resumePool = other.resumePool;

    for (const auto& req : other.requirements) {
        requirements.push_back(req->clone());
    }
}

ResumeSelectionSystem::ResumeSelectionSystem(const ResumeSelectionSystem& other) {
    copyFrom(other);
}

ResumeSelectionSystem& ResumeSelectionSystem::operator=(const ResumeSelectionSystem& other) {
    if (this == &other) {
        return *this;
    }

    free();
    copyFrom(other);
    return *this;
}

void ResumeSelectionSystem::addRequirement(const std::pair<std::string, std::string>& requirement) {
    requirements.push_back(RequirementFactory::create(requirement));
}

std::vector<std::string> ResumeSelectionSystem::addResume(const Resume& res) {
    if (resumePool.findByEmail(res.getEmail()).has_value()) {
        return { "Duplicate email." };
    }

    std::vector<std::string> errors;

    for (const auto& req : requirements) {
        auto checkRes = req->check(res);
        if (checkRes.has_value()) {
            errors.push_back(*checkRes);
        }
    }

    if (errors.empty()) {
        resumePool.add(res);
    }

    return errors;
}

std::optional<Resume> ResumeSelectionSystem::findResume(const std::string& email) const {
    return resumePool.findByEmail(email);
}

void ResumeSelectionSystem::removeResume(const std::string& email) {
    int prevSize = resumePool.size();

    resumePool.remove([email](const Resume& r)
        {
            return r.getEmail() == email;
        });

    if (prevSize == resumePool.size()) {
        throw std::invalid_argument("A resume with this email does not exist.");
    }
}

const ResumePool& ResumeSelectionSystem::getPool() const {
    return resumePool;
}