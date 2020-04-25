#include "Subject.hpp"
#include<cstring>

void Subject::copy(Subject const& other)
{
	strcmp(this->name, other.name);
	this->isObligatory = other.isObligatory;
}

Subject::Subject()
{
	strcpy(name, "");
	isObligatory = false;
}

Subject::Subject(const char name[], bool isObl)
{
	strcpy(this->name, name);
	this->isObligatory = isObl;
}

Subject::Subject(Subject& const other)
{
	copy(other);
}

Subject& Subject::operator=(Subject const& other)
{
	if (this != &other)
		copy(other);
	return *this;

}


