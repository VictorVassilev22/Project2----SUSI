#include "Specialty.hpp"
#include <cstring>

Specialty::Specialty()
{
	Program p("", "");
	this->program = p;
}

Specialty::Specialty(const char n[], const char pth[])
{
	Program p(n, pth);
	this->program = p;
}

bool Specialty::enrollStudent(Student const& s, size_t groupNum)
{		
	return groups[0][groupNum-1].addStudent(s);
}

bool Specialty::addStudent(Student const& s, size_t year, size_t groupNum)
{
	return groups[year - 1][groupNum - 1].addStudent(s);
}

void Specialty::deleteStudent(unsigned fn, size_t year, size_t groupNum)
{
	groups[year - 1][groupNum-1].deleteStudent(fn);
}

bool Specialty::findStudent(unsigned fn, size_t& year, size_t& groupNum, char*& name) const
{
	for (year = 0; year < MAX_YEARS; year++)
	{
		for (groupNum = 0; groupNum < MAX_GROUPS; groupNum++)
		{
			if (groups[year][groupNum].isStudentInGroup(fn, name)) {
				year++;
				groupNum++;
				return true;
			}
		}
	}
	return false;
}

Student Specialty::findStudent(unsigned fn) const
{
	Student s;
	for (size_t year = 0; year < MAX_YEARS; year++)
	{
		for (size_t groupNum = 0; groupNum < MAX_GROUPS; groupNum++)
		{
			s = groups[year][groupNum].findStudent(fn);
			if (s.getFn() == fn)
				break;
		}
	}
	return s;
}

bool Specialty::changeStudentStatus(unsigned fn, size_t index)
{
	for (size_t i = 0; i < MAX_YEARS; i++)
	{
		for (size_t j = 0; j < MAX_GROUPS; j++)
		{
			if (groups[i][j].changeStudentStatus(fn, index))
				return true;
		}
	}
	return false;
}
