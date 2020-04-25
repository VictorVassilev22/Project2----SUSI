#ifndef GROUP_H
#define GROUP_H
#include"Student.hpp"
#include<iostream>

const size_t MAX_STUDENTS = 20;
const size_t MAX_GROUPS = 8;
static unsigned group_num = 1;

class Group {
	unsigned number;
	Student students[MAX_STUDENTS];

public:
	Group();
	bool addStudent(Student const& s);
	void deleteStudent(size_t fn);
	bool isStudentInGroup(size_t fn, char*& name) const;
	Student findStudent(size_t fn) const;
	bool changeStudentStatus(size_t fn, size_t status);
};

#endif