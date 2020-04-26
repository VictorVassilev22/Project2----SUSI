#include<iostream>
#include"Specialty.hpp"
using namespace std;

///How many Specialties we want to have
const size_t MAX_SPEC = 2;
///Maximum symbols of a command
const size_t MAX_COMMAND = 15;
///maximum symbols for an option
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


///Template function to clear random type data from the heap
template<typename T>
void clear(T* data) {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

///Template function to check if data is dynamically located properly
template<typename T>
bool memCheck(T* data) {
	if (data==nullptr) {
		cout << "could not locate memory..." << endl;
		return false;
	}
	return true;
}

///Used to manually input the name of the specialties and paths for their programs from the user form command line
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

///searches Specialty by it's Program name
int search_Spec_By_Program_Name(char name[], Specialty* specs, size_t size) {
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(specs[i].getProgramName(), name) == 0) {
			return i;
		}
	}
	return -1;
}

///Resizes dynamically located char* variable
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


///Reads as much as you want long name from the console of from a txt file
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

///Reads faculty number, program and group and adds student.
///@see Specialty::enrollStudent()
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

///Reads faculty number, finds the student,  deletes it from that year.
///Creates new student with the same name (which was extracted) and advances it in year.
///puts it in the same group.
///@see Specialty::findStudent(unsigned, size_t&, size_t&, char*&) which extracts the name
///@see Specialty::deleteStudent() Specialty::addStudent()
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

///Finds student by faculty number 
///@param s extracts Student
///@param i extracts index of the Specialty
///@returns bool - is found or not
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

/// Finds student deletes it from the current group and adds it to another.
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

///changes only the group for now
///@see changeGroup() is used
void change(Specialty* specs) {
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

///changes Students's status
///@see Specialty::changeStudentStatus()
bool changeStatus(Specialty* specs, unsigned fn, size_t index) {
	for (size_t i = 0; i < MAX_SPEC; i++)
	{
		if (specs[i].changeStudentStatus(fn, index))
			return true;
	}
	return false;
}

///interrupts student. Changes it's status to interrupted
///@see changeStatus()
void interrupt(Specialty* specs) {
	unsigned fn;
	cin >> fn;
	if (!changeStatus(specs, fn, 1))
		cout << "Student not found!" << endl;
	else
		cout << "Student interrupted!" << endl;
}

///resumes student. Changes it's status to joined
///@see changeStatus()
void resume(Specialty* specs) {
	unsigned fn;
	cin >> fn;
	if (!changeStatus(specs, fn, 0))
		cout << "Student not found!" << endl;
	else
		cout << "Student resumed!" << endl;
}


///command controller is used to execute commends from the command line
///@returns bool - if the command was STOP_CMD or not
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

///Gets commands while commandController() returns true
///@see commandController().
void openCommandLine(Specialty* specs) {
	std::cout << "Command line is open (enroll, advance): " << std::endl;
	char command[MAX_COMMAND];

	do {
		std::cout << "Enter your command: ";
		std::cin >> command;
	} while (commandController(command, specs));

}

///Sets specialties, opens command controller, clears specialties
///@see setSpecialties() is used
///@see openCommandLine() is used
///@see clear() is used
int  main() {

	Specialty* specialties = nullptr;
	setSpecialties(specialties);
	openCommandLine(specialties);


	clear(specialties);
	return 0;
}