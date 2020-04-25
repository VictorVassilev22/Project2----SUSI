#include<iostream>
#include"Specialty.hpp"
using namespace std;
const size_t MAX_SPEC = 2;
const size_t MAX_COMMAND = 15;
const size_t MAX_OPTION = 8;
const char GROUP_OPT[] = "group" ;
const char YEAR_OPT[] = "year" ;
const char PROGRAM_OPT[] = "program" ;
const char STOP_CMD[] = "close" ;
const char ENROLL_CMD[] = "enroll";
const char ADVANCE_CMD[] = "advance";
const char CHANGE_CMD[] = "change";
const char INTERRUPT_CMD[] = "interrupt";
const char RESUME_CMD[] = "resume";

template<typename T>
void clear(T* data) {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

template<typename T>
bool memCheck(T* data) {
	if (data==nullptr) {
		cout << "could not locate memory..." << endl;
		return false;
	}
	return true;
}

void setSpecialties(Specialty*& specialties) {
	char program_name[MAX_NAME];
	char program_path[MAX_FILE_PATH];

	clear(specialties);
	specialties = new(nothrow) Specialty[MAX_SPEC];
	if (!memCheck(specialties))
		return;

	for (size_t i = 0; i < MAX_SPEC; i++)
	{
		cout << i+1 << ')' << endl;
		cout << "Enter program name: ";
		cin >> program_name;
		cout << "Enter file path: ";
		cin >> program_path;
		
		specialties[i] = Specialty(program_name, program_path);
	}
}

int search_Spec_By_Program_Name(char name[], Specialty* specs, size_t size) {
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(specs[i].getProgramName(), name) == 0) {
			return i;
		}
	}
	return -1;
}

void resizeStr(char*& str, size_t& size, size_t& to) {
	if (to == size) {
		size *= 2;
		char* new_name = new(std::nothrow) char[size];

		if (!memCheck(new_name)) {
			return;
		}

		for (size_t j = 0; j < to; j++)
		{
			new_name[j] = str[j];
		}

		clear(str);
		str = new_name;
	}
}

void getName(char*& str, size_t& size, std::istream& in) {
	char ch;
	size_t i = 0;
	while (in.peek() != EOF) {
		ch = in.peek();

		if (ch == '\n' || ch == '\r' || ch == '\0') {
			str[i] = '\0';
			return;
		}

		in.get(ch);
		resizeStr(str, size, i);
		str[i] = ch;

		i++;
	}
}

void enroll(Specialty* specs) {
	unsigned fn;
	char program[MAX_NAME];
	size_t group;
	size_t initial_name_size = 8; 
	char* name = new(nothrow) char[initial_name_size];
	if (!memCheck(name)) {
		return;
	}
	cin >> fn >> program >> group;
	int spec_index = search_Spec_By_Program_Name(program, specs, MAX_SPEC);
	if (spec_index < 0) {
		cout << "Specialty not found!" << endl;
		return;
	}
	if (group > MAX_GROUPS) {
		cout << "Invalid group!" << endl;
		return;
	}
	cin.ignore(); //ignores ' '
	getName(name, initial_name_size, cin);

	Student s(name, fn, group);
	specs[spec_index].enrollStudent(s, group);
	cout << "Student successfuly added in first year in " << program << "!" << endl;
}

void advance(Specialty* specs) {
	unsigned fn;
	cin >> fn;
	if (fn <= 0) {
		cout << "Invalid faculty number, please try again!" << endl;
		return;
	}

	size_t year = 0;
	size_t group = 0;
	char* name = nullptr;
	for (size_t i = 0; i < MAX_SPEC; i++)
	{
		if (specs[i].findStudent(fn, year, group, name)) {
			specs[i].deleteStudent(fn, year, group);
			if (year >= MAX_YEARS)
				cout << "Student is in 4-th year, no more advancements." << endl;
			else
			{
				Student s(name, fn, group);
				specs[i].addStudent(s, year + 1, group);
				cout << "Student successfuly advanced in " << year + 1 << " year!" << endl;
			}
			return;
		}
	}
	cout << "Student not found, try again" << endl;
}

bool findStudent(unsigned fn, Specialty* specs, Student& s, size_t& i) {
	for (i = 0; i < MAX_SPEC; i++)
	{
		s = specs[i].findStudent(fn);

		if (s.getFn() == fn) {
			return true;
		}
	}

	cout << "Student not found, try again" << endl;
	return false;
}

void changeGroup(Specialty* specs, unsigned fn, unsigned group) {
	Student s;
	size_t i = 0;
	bool isFound = false;

	if (!findStudent(fn, specs, s, i)) {
		cout << "Student not found, try again" << endl;
		return;
	}

	unsigned year = s.getYear();
	specs[i].deleteStudent(fn, year, s.getGroup());
	specs[i].addStudent(s, year, group);
	cout << "Student group changed to " << group << '!' << endl;
}

void change(Specialty* specs) { //changes only the group for now
	unsigned fn;
	cin >> fn;

	char option[MAX_OPTION];
	cin >> option;

	unsigned value;
	cin >> value;

	if (strcmp(option, GROUP_OPT) == 0) {
		changeGroup(specs, fn, value);
	}
	else if (strcmp(option, YEAR_OPT) == 0) {
		cout << "Coming soon..." << endl;
	}
	else if (strcmp(option, PROGRAM_OPT) == 0) {
		cout << "Coming soon..." << endl;
	}
}

bool changeStatus(Specialty* specs, unsigned fn, size_t index) {
	for (size_t i = 0; i < MAX_SPEC; i++)
	{
		if (specs[i].changeStudentStatus(fn, index))
			return true;
	}
	return false;
}

void interrupt(Specialty* specs) {
	unsigned fn;
	cin >> fn;
	if (!changeStatus(specs, fn, 1))
		cout << "Student not found!" << endl;
	else
		cout << "Student interrupted!" << endl;
}

void resume(Specialty* specs) {
	unsigned fn;
	cin >> fn;
	if (!changeStatus(specs, fn, 0))
		cout << "Student not found!" << endl;
	else
		cout << "Student resumed!" << endl;
}

bool commandController(char command[MAX_COMMAND], Specialty* specs) {

	if (strcmp(command, STOP_CMD) == 0)
		return false;
	else if (strcmp(command, ENROLL_CMD) == 0)
		enroll(specs);
	else if (strcmp(command, ADVANCE_CMD) == 0)
		advance(specs);
	else if (strcmp(command, CHANGE_CMD) == 0)
		change(specs);
	else if (strcmp(command, INTERRUPT_CMD) == 0)
		interrupt(specs);
	else if (strcmp(command, RESUME_CMD) == 0)
		resume(specs);

	return true;
}

void openCommandLine(Specialty* specs) {
	std::cout << "Command line is open (enroll, advance): " << std::endl;
	char command[MAX_COMMAND];

	do {
		std::cout << "Enter your command: ";
		std::cin >> command;
	} while (commandController(command, specs));

}

int  main() {

	Specialty* specialties = nullptr;
	setSpecialties(specialties);
	openCommandLine(specialties);


	clear(specialties);
	return 0;
}