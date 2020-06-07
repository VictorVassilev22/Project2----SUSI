#include "Student.hpp"
#include<iostream>

Student::Student()
{
	copyRequired();
	name = nullptr;
	f_num = 0;
	group = 0;
	setStatus(0);
	year = 0;
}

Student::Student(const char* name, unsigned f_num, size_t group, Specialty& sp, unsigned year) 
{
	if (f_num == 0) {
		std::cout << "0 is invalid value for faculty number, please try again!" << std::endl;
		return;
	}
	specialty = sp;
	copyRequired();
	this->name = nullptr;
	setName(name);
	this->f_num = f_num;
	this->group = group;
	setStatus(0);
	this->year = year;
}

Student::Student(Student const& other)
{
	copy(other);
}

Student::~Student()
{
	clear(name);
}

Student& Student::operator=(Student const& other)
{
	if (this != &other) {
		copy(other);
	}
	return *this;
}

bool Student::hasYearForCourse(unsigned sub, bool isRequired)
{
	unsigned year_required = 0;
	if (isRequired) {
		year_required = year_to_take_rs[sub];
		if (year_required > year) {
			std::cout << "Year " << year_required << " is required to take this subject!" << std::endl;
			return false;
		}
	}
	else {
		year_required = year_to_take_es[sub];
		if (year_required > year) {
			std::cout << "Year " << year_required << " is required to take this subject!" << std::endl;
			return false;
		}
	}

	return true;
}

char* Student::getName() const
{
	if (!name) {
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

double Student::getGrade(unsigned i, bool isRequired) const
{
	double grade = 0.0;
	if (isRequired) {
		grade = required_grades[i];
		if (i >= MAX_R_SUB) {
			std::cout << "No such subject exists!" << std::endl;
			return 0.0;
		}
		if (!specialty.hasSubject(i)) {
			std::cout << "This subject is not part of the program!" << std::endl;
			return 0.0;
		}
		
		if (grade < MIN_PASS_GRADE && grade >=MIN_GRADE)
			return MIN_GRADE;
		else
			return grade;

	}
	else {
		grade = elective_grades[i];
		if (i >= MAX_E_SUB) {
			std::cout << "No such subject exists!" << std::endl;
			return 0.0;
		}
		if (!specialty.hasSubject(i, false)) {
			std::cout << "This subject is not part of the program!" << std::endl;
			return 0.0;
		}

		if (grade < MIN_PASS_GRADE && grade >= MIN_GRADE)
			return MIN_GRADE;
		else
			return grade;
	}
}

double Student::getAverageGrade() const
{
	double grade = 0.0;;
	double grades_sum = 0.0;
	unsigned grades_count = 0;
	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		if(specialty.hasSubject(i))
			grade = getGrade(i);

		if (specialty.hasSubject(i) && year_to_take_rs[i] <= year && grade>=MIN_GRADE) {
			grades_sum += grade;
			grades_count++;
		}
	}

	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		if(specialty.hasSubject(i,false))
			grade = getGrade(i,false);

		if (specialty.hasSubject(i, false) && year_to_take_es[i] <= year && grade >= MIN_GRADE) {
			grades_sum += getGrade(i, false);
			grades_count++;
		}
	}

	if (grades_count == 0)
		return MIN_GRADE;

	double average_grade = grades_sum / grades_count;
	return average_grade;
}

void Student::printStatus() const
{
	if (status[0]) {
		std::cout << "Studying";
	}
	else if (status[1]) {
		std::cout << "Interrupted";
	}
	else {
		std::cout << "Graduated";
	}
}

unsigned Student::getStatus() const
{
	for (size_t i = 0; i < STATUS_MAX; i++)
	{
		if (status[i])
			return i;
	}
}

void Student::report() const
{
	
	const char* p_name = specialty.getName();

	std::cout << "Student name: " << name << std::endl;
	std::cout << "Faculty number: " << f_num << std::endl;
	std::cout << "Program: " << p_name << std::endl;
	std::cout << "Year: " << year << std::endl;
	std::cout << "Group: " << group << std::endl;
	std::cout << "Status: ";
	printStatus();
	std::cout<<std::endl;
	std::cout << "Taken subjects:" << std::endl;

	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		if (hasRequired(i)) {
			if (year_to_take_rs[i] <= year && required_grades[i]>=MIN_PASS_GRADE) {
				std::cout << "Subject: " << specialty.getSubjectName(i) << " Grade: " << getGrade(i) << std::endl;
			}
		}
	}

	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		if (hasElective(i)) {
			if (year_to_take_es[i] > year && elective_grades[i] >= MIN_PASS_GRADE) {
				std::cout << "Subject: " << specialty.getSubjectName(i, false) << " Grade: " << getGrade(i, false) << std::endl;
			}
		}
	}

	std::cout << "Not taken subjects:" << std::endl;

	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		if (hasRequired(i)) {
			if (year_to_take_rs[i] <= year && required_grades[i] < MIN_PASS_GRADE) {
				std::cout << "Subject: " <<specialty.getSubjectName(i) << " Grade: " << MIN_GRADE << std::endl;
			}
		}
	}

	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		if (hasElective(i)) {
			if (year_to_take_es[i] <= year && elective_grades[i] < MIN_PASS_GRADE) {
				std::cout << "Subject: " << specialty.getSubjectName(i, false) << " Grade: " << MIN_GRADE << std::endl;
			}
		}
	}

	double average_grade = getAverageGrade();

	std::cout << "Avarege grade: " << average_grade << std::endl;

	delete[] p_name;
}

void Student::print() const
{
	const char* p_name = specialty.getName();

	std::cout << "Student name: " << name << std::endl;
	std::cout << "Faculty number: " << f_num << std::endl;
	std::cout << "Program: " << p_name << std::endl;
	std::cout << "Year: " << year << std::endl;
	std::cout << "Group: " << group << std::endl;
	std::cout << "Status: ";
	printStatus();
	std::cout << std::endl;
	double average_grade = getAverageGrade();
	std::cout << "Avarege grade: " << average_grade << std::endl;
	delete[] p_name;
}

bool Student::enrollinElective(unsigned index)
{
	unsigned course_year = year_to_take_es[index];

	if (!specialty.hasSubject(index, false)) {
		std::cout << "Student\'s program does not contain that course!" << std::endl;
		return false;
	}

	if (hasInterrupted()) {
		std::cout << "This student has interrupted, and cannot take that course!" << std::endl;
		return false;
	}

	if (year < course_year) {
		std::cout << "This course requires year " << course_year << " to be taken!" << std::endl;
		return false;
	}

	electives[index] = true;
	return true;
}

bool Student::enrollinRequired(unsigned index)
{
	unsigned course_year = year_to_take_rs[index];

	if (hasInterrupted()) {
		std::cout << "This student has interrupted, and cannot take that course!" << std::endl;
		return false;
	}

	if (year < course_year) {
		std::cout << "This course requires year " << course_year << " to be taken!" << std::endl;
		return false;
	}

	required[index] = true;
	return true;
}

void Student::addGrade(double grade, size_t subject, bool isRequired)
{
	if (!hasYearForCourse(subject, isRequired)) {
		return;
	}

	if (grade < MIN_GRADE) {
		grade = MIN_GRADE;
	}
	else if (grade > MAX_GRADE) {
		grade = MAX_GRADE;
	}

	if (isRequired)
		required_grades[subject] = grade;
	else
		elective_grades[subject] = grade;
}

void Student::printProtocolCourse(unsigned sub, bool isRequired) const
{
	const char* p_name = specialty.getName();
	std::cout << "Student name: " << name << ' ';
	std::cout << "Faculty number: " << f_num << ' ';
	std::cout << "Program: " << p_name << std::endl;
	std::cout << "Year: " << year << std::endl;

	std::cout << "Grade: ";
	if (isRequired) {
		std::cout << required_grades[sub];
	}
	else {
		std::cout << required_grades[sub];
	}
	std::cout << std::endl;

	delete[] p_name;
}

void Student::setStatus(size_t index)
{
	if (index >= STATUS_MAX) {
		std::cout << "Invalid status, try again!" << std::endl;
		return;
	}

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

//void Student::copySubjects(TakenSubject const* src)
//{
//	if (subjects == nullptr) {
//		if (subjects_size > 0)
//			subjects = new TakenSubject[subjects_size];
//		else
//			return;
//	}
//
//	for (size_t i = 0; i < subjects_size; i++)
//	{
//		subjects[i] = src[i];
//	}
//}

void Student::copy(Student const& other)
{
	specialty = other.specialty;
	setName(other.name);
	this->f_num = other.f_num;
	this->group = other.group;
	this->year = other.year;
	copyStatus(other.status);

	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		electives[i] = other.electives[i];
	}

	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		required[i] = other.required[i];
	}

	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		required_grades[i] = other.required_grades[i];
	}

	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		elective_grades[i] = other.elective_grades[i];
	}
}


template<typename T>
void Student::clear(T*& data) {
	if (data) {
		delete[] data;
		data = nullptr;
	}
}

void Student::setName(const char* other_name) {
	/*if (name != nullptr)*/
		clear(name);
	if (!other_name) {
		name = nullptr;
		return;
	}

	if (other_name[0] == '#') {
		std::cout << "# symbol is reserved and cannot be used! Name is not set, try again!" << std::endl;
		return;
	}

	name = new(std::nothrow) char[strlen(other_name) + 1];

	if (!name) {
		std::cout << "could not allocate memory" << std::endl;
		return;
	}

	strcpy(name, other_name);
}

void Student::changeGroup(size_t new_group)
{
	if (new_group > MAX_GROUP) {
		std::cout << "Error! group " << new_group << " does not exist" << std::endl;
		return;
	}

	group = new_group;
	std::cout << "Student switched in group " << new_group << std::endl;
}

bool Student::changeYear(unsigned new_year)
{
	unsigned unpassed = 0;
	if (new_year > year + 1) {
		std::cout << "Student cannot skip years! This student is currently in " << year << " year! Please, advance in next!"<<std::endl;
		return false;
	}

	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		if (!checkIfPassed(i) && year_to_take_rs[i]<=year) {
			unpassed++;
		}

		if (unpassed > 2) {
			std::cout << "Student has not passed all of his required subjects and cannot advance in year!" << std::endl;
			return false;
		}
	}

	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		if (!checkIfPassed(i, false) && year_to_take_rs[i] <= year && hasElective(i)) {
			unpassed++;
		}

		if (unpassed > 2) {
			std::cout << "Student has not passed all of his required subjects and cannot advance in year!" << std::endl;
			return false;
		}
	}

	year = new_year;
	return true;
}

bool Student::checkIfPassed(unsigned subject, bool isRequired)
{
	if (isRequired) {

		if (subject >= MAX_R_SUB) {
			std::cout << "This subject does not exist!" << std::endl;
			return false;
		}
	
		if (specialty.hasSubject(subject) && required_grades[subject] < 3.00 || year_to_take_rs[subject] > year)
			return false;

			return true;
	}
	else {

		if (subject >= MAX_E_SUB) {
			std::cout << "This subject does not exist!" << std::endl;
			return false;
		}

		if ((specialty.hasSubject(subject, false) && elective_grades[subject] < 3.00) || year_to_take_es[subject] > year)
			return false;

		return true;
	}
}

bool Student::isQualifiedForSpecialty(Specialty const& spec)
{
	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		if (spec.hasSubject(i) && required_grades[i] < MIN_GRADE) {
			return false;
		}
	}
	return true;
}

void Student::copyRequired()
{
	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		required[i] = specialty.hasSubject(i);
	}
}
