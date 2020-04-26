#ifndef GROUP_H
#define GROUP_H
#include"Student.hpp"
#include<iostream>

///Indicates how many students are there in a group
const size_t MAX_STUDENTS = 20;
///Indicates how many groups is maximim for a Specialty
const size_t MAX_GROUPS = 8;
///This static member keeps count of the numbers of the groups.
/// in Group::Group(), Group::number is assigned to group_num and group_num is increased with 1.
static unsigned group_num = 1;

///Realization of Group class.
///Stores a bunch of students in a group.
///@note Due to exessive use of linear search, I consider moving it to it's own function.
///@note Maybe remove this class altogether and use unly Student::group to indicate Student's group.

class Group {
	///Indicates the number of the Group
	unsigned number;
	///Stores all students in this Group.
	Student students[MAX_STUDENTS];

public:
	///Default constructor sets the number of the group
	///@see group_num
	Group();
	///If the array isn't full, sets a Student at the last available position of the array.
	bool addStudent(Student const& s);
	/// @param fn This parameter is used to search the Student by it's Student::f_num
	///If Student with such faculy number exists rewrites it with a default member variables.
	///@see Student::Student()
	void deleteStudent(size_t fn);
	/// Uses linear search to find student by it's faculty number.
	///@param name It's pointer is passed by reference, because it is thought to be extracted from the search.
	///@returns Bool value which indicates if the student is found and if it's name is extracted properly.
	///@see Student::getName() Specialty::findStudent()
	bool isStudentInGroup(size_t fn, char*& name) const;
	///Uses linear search to find a student.
	///@returns Object Student equal to student we are searching. If not found, returns default(invalid) Student.
	///@see Student::Student()
	Student findStudent(size_t fn) const;
	///Uses linear search to find student and changes it's status to desired.
	///@param status Indicates which status we want to set to the Student.
	///@see Student::status Student::setStatus()
	bool changeStudentStatus(size_t fn, size_t status);
};

#endif