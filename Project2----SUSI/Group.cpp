#include "Group.hpp"

Group::Group()
{
	if (group_num > MAX_GROUPS)
		group_num = 1;

	number = group_num++;
}

bool Group::addStudent(Student const& s)
{
	size_t index=0;
	while (index < MAX_STUDENTS) {
		if (students[index].getFn() == 0) {
			students[index] = s;
			return true;
		}
		index++;
	}
	std::cout << "Current group is full. Try adding this student in another one." << std::endl;
	return false;
}

void Group::deleteStudent(size_t fn)
{
	for (size_t i = 0; i < MAX_STUDENTS; i++)
	{
		if (students[i].getFn() == fn) {
			students[i] = Student();
		}
	}
}

bool Group::isStudentInGroup(size_t fn, char*& name) const
{
	for (size_t i = 0; i < MAX_STUDENTS; i++)
	{
		if (students[i].getFn() == fn) {
			name = students[i].getName();
			return true;
		}
	}
	return false;
}

Student Group::findStudent(size_t fn) const
{
	Student s;
	for (size_t i = 0; i < MAX_STUDENTS; i++)
	{
		if (students[i].getFn() == fn) {
			s = students[i];
			break;
		}
	}
	return s;
}

bool Group::changeStudentStatus(size_t fn, size_t index)
{
	for (size_t i = 0; i < MAX_STUDENTS; i++)
	{
		if (students[i].getFn() == fn) {
			students[i].setStatus(index);
			return true;
		}
	}

	return false;
}
