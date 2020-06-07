#include "Specialty.hpp"

void Specialty::setRequired(const unsigned origin[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		unsigned index = origin[i];
		required[index] = true;
	}
}

void Specialty::setElectives(const unsigned origin[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		unsigned index = origin[i];
		electives[index] = true;
	}
}

void Specialty::setName(char const* other_name)
{
	if (name) {
		delete[] name;
		name = nullptr;
	}

	if (!other_name) {
		name = nullptr;
		return;
	}

	if (other_name[0] == '#') {
		std::cout << "# symbol is reserved and cannot be used! Program name is not set, try again!" << std::endl;
		return;
	}

	name = new(std::nothrow) char[strlen(other_name) + 1];

	if (!name) {
		std::cout << "could not allocate memory" << std::endl;
		return;
	}

	strcpy(name, other_name);
}

void Specialty::copy(Specialty const& other)
{
	setName(other.name);
	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		electives[i] = other.electives[i];
	}

	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		required[i] = other.required[i];
	}
}

bool Specialty::hasSubject(unsigned sub, bool isRequired) const
{
	if (isRequired) {
		return required[sub];
	}
	else {
		return electives[sub];
	}
}

char* Specialty::getName() const
{
	if (!name) {
		std::cout << "Error getting name!" << std::endl;
		return nullptr;
	}
	char* name_cpy = new(std::nothrow) char[strlen(name) + 1];
	if (!name_cpy) {
		std::cout << "Error getting name!" << std::endl;
		return nullptr;
	}
	strcpy(name_cpy, name);
	return name_cpy;

}

Specialty& Specialty::operator=(Specialty const& other)
{
	if (this != &other) {
		copy(other);
	}
	return *this;
}

const char* Specialty::getSubjectName(size_t i, bool isRequired) const
{
	if (isRequired) {
		if (i >= MAX_R_SUB) {
			std::cout << "No such subject!" << std::endl;
			return nullptr;
		}
		return all_required_subjects[i];
	}
	else {
		if (i >= MAX_E_SUB) {
			std::cout << "No such subject!" << std::endl;
			return nullptr;
		}
		return all_elective_subjects[i];
	}
}

int Specialty::getRequiredSubject(const char* name) const
{
	int index = -1;
	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		if (strcmp(name, all_required_subjects[i])==0) {
			index = i;
			break;
		}
	}
	return index;
}

int Specialty::getElectiveSubject(const char* name) const
{
	int index = -1;
	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		if (strcmp(name, all_elective_subjects[i])==0) {
			index = i;
			break;
		}
	}
	return index;
}

Specialty::Specialty(char const* name, const unsigned required[], size_t size_r, const unsigned electives[], size_t size_e) : name(nullptr)
{
	setName(name);
	setRequired(required, size_r);
	setElectives(electives, size_e);
}

Specialty::Specialty()
{
	//setName(DEF_NAME);
	name = nullptr;
}

Specialty::Specialty(Specialty const& other)
{
	copy(other);
}

Specialty::~Specialty()
{
	if (name) {
		delete[] name;
		name = nullptr;
	}
}

unsigned Specialty::getSubjectYear(bool isRequired, size_t index) const
{
	if (isRequired)
		return year_to_take_rs[index];
	else
		return year_to_take_es[index];
}
