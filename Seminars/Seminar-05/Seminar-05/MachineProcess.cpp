#include "MachineProcess.h"
#include <cstring>
#include <iostream>
#pragma warning (disable:4996)

int MachineProcess::processesCount = 0;

void MachineProcess::copyFrom(const MachineProcess& other) {
	setPid(other.pid);
	setName(other.name);
	setMemory(other.memory);
}

void MachineProcess::free() {
	delete[] name;
	name = nullptr;
	pid = 0;
	memory = 0;
}

MachineProcess::MachineProcess(int pid, const char* name, int memory) : name(nullptr) {
	setPid(pid);
	setName(name);
	setMemory(memory);
	processesCount++;
}

MachineProcess::MachineProcess(const MachineProcess& other) :name(nullptr) {
	copyFrom(other);
	processesCount++;
}

MachineProcess& MachineProcess::operator=(const MachineProcess& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

MachineProcess::~MachineProcess() {
	free();
	processesCount--;
}

int MachineProcess::getPid() const {
	return pid;
}

int MachineProcess::getMemory() const {
	return memory;
}

const char* MachineProcess::getName() const {
	return name;
}

int MachineProcess::getProcessesCount() {
	return processesCount;
}

void MachineProcess::setPid(int pid) {
	if (pid < 0) {
		this->pid = 0;
		return;
	}

	this->pid = pid;
}

void MachineProcess::setName(const char* name) {
	delete[] this->name;

	if (!name || strlen(name) == 0) {
		this->name = new char[strlen("Unknown") + 1];
		strcpy(this->name, "Unknown");
		return;
	}

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void MachineProcess::setMemory(int memory) {
	if (memory < 0) {
		this->memory = 0;
		return;
	}

	this->memory = memory;
}

void MachineProcess::print() const {
	std::cout << "PID: " << pid << ", Name: " << name << ", Size: " << memory << " MB" << std::endl;
}

bool MachineProcess::hasMoreMemoryThan(const MachineProcess& other) const {
	return memory > other.memory;
}
