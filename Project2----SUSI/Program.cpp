#include "Program.hpp"
#include<cstring>

void Program::copy(Program const& other)
{
	strcpy(this->name, other.name);
	strcpy(this->path, other.path);
	copySubjects(this->subjects, other.subjects);
}

void Program::copySubjects(SpecSubject dest[], SpecSubject const src[])
{
	for (size_t i = 0; i < MAX_SUBJECTS; i++)
	{
		dest[i].sub = src[i].sub;
		dest[i].year = src[i].year;
	}
}

Program::Program()
{
	strcpy(name, "");
	strcpy(path, "");
}

Program::Program(const char name[], const char path[])
{
	strcpy(this->name, name);
	strcpy(this->path, path);
}

Program::Program(Program const& other)
{
	copy(other);
}

Program& Program::operator=(Program const& other)
{
	if (this != &other) {
		copy(other);
	}
	return *this;
}

char* Program::getName() const
{
	char* name_cpy = new(std::nothrow) char[strlen(name) + 1];
	strcpy(name_cpy, name);
	return name_cpy;
}


SpecSubject::SpecSubject()
{
	sub = Subject("", false);
	year = 1;
}
