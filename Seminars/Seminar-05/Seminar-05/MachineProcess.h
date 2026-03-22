#pragma once
class MachineProcess {
private:
	int pid;
	char* name;
	int memory;
	static int processesCount;

	void copyFrom(const MachineProcess& other);
	void free();

public:
	MachineProcess(int pid, const char* name, int memory);
	MachineProcess(const MachineProcess& other);
	MachineProcess& operator=(const MachineProcess& other);
	~MachineProcess();

	int getPid() const;
	const char* getName() const;
	int getMemory() const;
	static int getProcessesCount();

	void setPid(int pid);
	void setName(const char* name);
	void setMemory(int memory);
	void print() const;
	bool hasMoreMemoryThan(const MachineProcess& other) const;
};

