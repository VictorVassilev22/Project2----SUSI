#include "UserInterface.hpp"


char* readStrSUSI(std::istream& in, bool hasSpaces, size_t size)
{
	char break_symbol = hasSpaces ? '\n' : ' ';
	char* name = new(std::nothrow) char[size];
	if (!name) {
		std::cout << "Error locating memory for specialty name!" << std::endl;
		return nullptr;
	}
	in.ignore(); // ignores space
	size_t i = 0;
	char ch = in.get();
	while (ch != break_symbol)
	{
		if (ch == '\n')
			break;

		name[i] = ch;
		i++;

		if (i >= size - 1) {
			std::cout << "Maximum symbols for name reached! This string might be shortened." << std::endl;
			break;
		}
		ch = in.get();
	}
	name[i] = '\0';
	return name;
}

bool UserInterface::commandController(char command[])
{


	if (strcmp(command, STOP_CMD) == 0)
		return false;
	else if (strcmp(command, ENROLL_CMD) == 0)
		enroll();
	else if (strcmp(command, ADVANCE_CMD) == 0)
		advance();
	else if (strcmp(command, CHANGE_CMD) == 0)
		change();
	else if (strcmp(command, INTERRUPT_CMD) == 0)
		interrupt();
	else if (strcmp(command, RESUME_CMD) == 0)
		resume();
	else if (strcmp(command, PRINT_CMD) == 0)
		print();
	else if (strcmp(command, PRINTALL_CMD) == 0)
		printall();
	else if (strcmp(command, ENROLLIN_CMD) == 0)
		enrollin();
	else if (strcmp(command, ADDGRADE_CMD) == 0)
		addGrade();
	else if (strcmp(command, PROTOCOL_CMD) == 0)
		protocol();
	else if (strcmp(command, REPORT_CMD) == 0)
		report();
	else if (strcmp(command, SAVE_CMD) == 0)
		save();
	else if (strcmp(command, SAVEAS_CMD) == 0)
		saveAs();
	else if (strcmp(command, HELP_CMD) == 0)
		help();
	else {
		cout << "You entered invalid command, please try again!" << endl;
		char line[MAX_LINE];
		cin.getline(line, MAX_LINE);
	}
	return true;
}

void UserInterface::enroll()
{
	unsigned f_num = 0;
	size_t group = 0;
	const char* specialty_name = new(std::nothrow) char[MAX_NAME];
	if (!memCheck(specialty_name))
		return;
	const char* student_name = new(std::nothrow) char[MAX_NAME];
	if (!memCheck(student_name))
		return;
	std::cin >> f_num;
	specialty_name = readStrSUSI(std::cin, false, MAX_NAME); 
	std::cin >> group;
	student_name = readStrSUSI(std::cin, true, MAX_NAME);
	system.enroll(f_num, specialty_name, group, student_name);
	clear(specialty_name);
}

void UserInterface::advance()
{
	unsigned fn;
	std::cin >> fn;
	system.advance(fn);
}

void UserInterface::change()
{
	char ch;
	unsigned fn;
	cin >> fn;
	
	char option[MAX_OPTION];
	cin >> option;
	
	unsigned value;
	char* str_value = nullptr;

	/*cin.ignore();
	ch = cin.peek();

	if (ch >= '0' && ch <= '9')
		cin >> value;
	else {
		str_value = readStr(cin, false, MAX_NAME);
		if (!memCheck(str_value))
			return;
	}*/

	
	if (strcmp(option, GROUP_OPT) == 0) {
		cin.ignore();
		cin >> value;
		system.changeGroup(fn, value);
	}
	else if (strcmp(option, YEAR_OPT) == 0) {
		cin.ignore();
		cin >> value;
		system.changeYear(fn, value);
	}
	else if (strcmp(option, PROGRAM_OPT) == 0) {
		str_value = readStrSUSI(cin, false, MAX_NAME);
		if (!memCheck(str_value))
			return;
		system.changeSpecialty(fn, str_value);
	}

	clear(str_value);
}

void UserInterface::graduate()
{
	unsigned fn;
	cin >> fn;
	system.graduate(fn);
}

void UserInterface::interrupt()
{
	unsigned fn;
	cin >> fn;
	system.interrupt(fn);
}

void UserInterface::print() const
{
	unsigned fn;
	cin >> fn;
	system.print(fn);
}

void UserInterface::printall()
{
	unsigned year;
	//cin.ignore();
	char* program = readStrSUSI(cin, false, MAX_NAME);
	if (!memCheck(program))
		return;
	cin >> year;
	system.printAll(program, year);
	clear(program);
}

void UserInterface::enrollin()
{
	unsigned fn;
	cin >> fn;
	//cin.ignore();
	char* course = readStrSUSI(cin, true, MAX_NAME);
	if (!memCheck(course))
		return;
	system.enrollin(fn, course);
	clear(course);
}
 
void UserInterface::report() const
{
	unsigned fn;
	cin >> fn;
	system.report(fn);
}

void UserInterface::addGrade()
{
	unsigned fn;
	cin >> fn;
	double grade;
	cin >> grade;
	//cin.ignore();
	char* course = readStrSUSI(cin, true, MAX_NAME);
	if (!memCheck(course))
		return;
	system.addGrade(fn, course, grade);
	clear(course);
}

void UserInterface::protocol()
{
	char* course = readStrSUSI(cin, true, MAX_NAME);
	system.protocolAll(course);
}

void UserInterface::save() const
{
	system.save();
}

void UserInterface::saveAs() const
{
	system.saveAs();
}

void UserInterface::help() const
{
	std::cout << "Help menu:" << std::endl;
	std::cout << "To enroll student, enter command enroll <fn> <program> <group> < name>. Faculty number is never zero! Name cannot begin with #" << std::endl;
	std::cout << "To advance student enter command advance <fn>" << std::endl;
	std::cout << "To change program, group or year enter command change <fn> <option> <value>" << std::endl;
	std::cout << "To gradueate a student enter command graduate <fn>" << std::endl;
	std::cout << "To interrupt student enter command interrupt <fn>" << std::endl;
	std::cout << "To resume student enter command resume <fn>" << std::endl;
	std::cout << "To print student enter command print <fn>" << std::endl;
	std::cout << "To print all student from a program and a year enter command printall <program> <year>" << std::endl;
	std::cout << "To enrollin a course for a student enter command enrollin <fn> <course>" << std::endl;
	std::cout << "To add grade for a student enter command addgrade <fn> <grade> <course>" << std::endl;
	std::cout << "To print a protocol for a course enter command protocol <course>" << std::endl;
	std::cout << "To print a report for a student enter command report <fn>" << std::endl;
	std::cout << "To to save the current data enter command save" << std::endl;
	std::cout << "To to save the current data in a desired file enter command saveas <file name>. WARNING: The program does not load data from non-specified files!" << std::endl;
	std::cout << "To close the application enter command close" << std::endl;
}

void UserInterface::resume()
{
	unsigned fn;
	cin >> fn;
	system.resume(fn);
}

void UserInterface::openCommandLine()
{
	std::cout << "Command line is open (enroll, advance): " << std::endl;
	char command[MAX_COMMAND];

	do {
		std::cout << "Enter your command: ";
		std::cin >> command;
	} while (commandController(command));
}
