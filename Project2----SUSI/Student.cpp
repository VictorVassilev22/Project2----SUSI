#include "Student.hpp"
#include<iostream>

Student::Student()
{
	name = new(std::nothrow) char[1];
	if(name)
		name[0] = '\0';
	else{
		std::cout << "Constructor error: name could not alloc memory!";
	}
	f_num = 0;
	group = 0;
	setStatus(0);
	year = 0;
	avarege_grade = 0.0;
	subjects = nullptr;
	subjects_capacity = DEF_CAPACITY;
	subjects_size = 0;
}

Student::Student(char* name, unsigned f_num, unsigned group, unsigned year)
{
	setName(name);
	this->f_num = f_num;
	this->group = group;
	setStatus(0);
	avarege_grade = 0.0;
	this->year = year;
	subjects = nullptr;
	subjects_capacity = DEF_CAPACITY;
	subjects_size = 0;
}

Student::Student(Student const& other)
{
	copy(other);
}

Student::~Student()
{
	clear(name);
	clear(subjects);
}

Student& Student::operator=(Student const& other)
{
	if (this != &other) {
		copy(other);
	}
	return *this;
}

char* Student::getName() const
{
	char* name_cpy = new(std::nothrow) char[strlen(name) + 1];
	strcpy(name_cpy, name);
	return name_cpy;

}

void Student::setStatus(size_t index)
{
	for (size_t i = 0; i < STATUS_MAX; i++)
	{
		if (i == index)
			status[i] = true;
		else
			status[i] = false;
	}
}

void Student::copyStatus(bool const src[])
{
	for (size_t i = 0; i < STATUS_MAX; i++)
	{
		status[i] = src[i];
		if (status[i] == true)
			break;
	}
}

void Student::copySubjects(TakenSubject const* src)
{
	if (subjects == nullptr) {
		if (subjects_size > 0)
			subjects = new TakenSubject[subjects_size];
		else
			return;
	}

	for (size_t i = 0; i < subjects_size; i++)
	{
		subjects[i] = src[i];
	}
}

void Student::copy(Student const& other)
{
	setName(other.name);
	this->f_num = other.f_num;
	this->group = other.group;
	this->year = other.year;
	copyStatus(other.status);
	this->avarege_grade = other.avarege_grade;
	copySubjects(other.subjects);
	this->subjects_capacity = other.subjects_capacity;
	this->subjects_size = other.subjects_size;
}


template<typename T>
void Student::clear(T* data) {
	delete[] data;
	data = nullptr;
}

void Student::setName(const char* other_name) {
	if (name != nullptr)
		clear(name);
	if (!other_name) {
		std::cout << "Error copying name!" << std::endl;
		return;
	}
	name = new(std::nothrow) char[strlen(other_name) + 1];

	if (!name) {
		std::cout << "could not allocate memory" << std::endl;
		return;
	}

	strcpy(name, other_name);
}

TakenSubject::TakenSubject()
{
	sub = Subject();
	exam = false;
	grade = 0.0;
}
