#ifndef FACULTY_H
#define FACULTY_H
#include"Group.hpp"

const size_t MAX_YEARS = 4;

class Specialty {
	Program program;
	Group groups[MAX_YEARS][MAX_GROUPS];

public:
	Specialty();
	Specialty(const char name[], const char program_path[]);
	char* getProgramName() { return program.getName(); }
	bool enrollStudent(Student const& s, size_t groupNum);
	bool addStudent(Student const& s, size_t year, size_t groupNum);
	void deleteStudent(unsigned fn, size_t year, size_t groupNum);
	bool findStudent(unsigned fn, size_t& year, size_t& groupNum, char*& name) const;
	Student findStudent(unsigned fn) const;
	bool changeStudentStatus(unsigned fn, size_t index);

};

#endif