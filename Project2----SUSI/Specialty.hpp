#ifndef FACULTY_H
#define FACULTY_H
#include"Group.hpp"

///Indicates how many years of studying a Student could take.
const size_t MAX_YEARS = 4;

///Realization of Specialty class
///
///A specialty stores students in a matrix of Groups, and has it's own Program of Subjects to follow.

class Specialty {
	///A Program of Subjects for this specialty.
	Program program;
	///Matrix of Groups(of Students). MAX_YEARS rows indicating which year Students are currently studying, with MAX_GROUPS in each.
	Group groups[MAX_YEARS][MAX_GROUPS];

public:
	///Default constructor. Sets invalid ("") values for the Specialty::program
	///@see Program::Program() is used
	Specialty();
	///Constructor sets name of the Specialty::program an it's path
	///@see program::Program(const char, const char); is used
	Specialty(const char name[], const char program_path[]);
	///@returns Program::getName() for the current Specialty::program
	char* getProgramName() { return program.getName(); }
	///@returns bool if the student is successfully enrolled
	///Adds a new Student in year 1 in Group @param groupNum
	///Adds in Group::groups in position [0][groupNum -1]
	///@see Group::addStudent() is used
	bool enrollStudent(Student const& s, size_t groupNum);
	///Adds student in desired group and desired year.
	///@see Group::addStudent() is used
	bool addStudent(Student const& s, size_t year, size_t groupNum);
	///Deletes student found by faculty number.
	///@see Group::deleteStudent() is used
	void deleteStudent(unsigned fn, size_t year, size_t groupNum);
	///Searches through all the years and their groups to find a student.
	///@param name Used to extract Student's name in it
	///@param year Used to extract Student's year in it
	///@see Group::isStudentInGroup() is used
	bool findStudent(unsigned fn, size_t& year, size_t& groupNum, char*& name) const;
	///Creates variable Student s; assignes found student to it and returns it
	///@see Group::findStudent() is used
	///@returns Student s;
	Student findStudent(unsigned fn) const;
	/// Sets status of a student
	///@param index indicates which status to assign
	///@see Student::status Student::setStatus()
	///@see Group::changeStudentStatus() is used
	bool changeStudentStatus(unsigned fn, size_t index);

};

#endif