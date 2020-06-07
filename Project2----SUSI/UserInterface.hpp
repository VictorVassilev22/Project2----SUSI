#ifndef UI_H
#define UI_H
#include<iostream>
#include"SUSI.hpp"
using namespace std;

///Maximum symbols of a command
const size_t MAX_COMMAND = 15;
///maximum symbols for an option
const size_t MAX_OPTION = 8;
//size for a line to clean buffer
const size_t MAX_LINE = 100;

/// <summary>
/// This and the following const char arrays are constats of command which the user enters
/// </summary>

const char GROUP_OPT[] = "group";
const char YEAR_OPT[] = "year";
const char PROGRAM_OPT[] = "program";
const char STOP_CMD[] = "close";
const char ENROLL_CMD[] = "enroll";
const char ADVANCE_CMD[] = "advance";
const char CHANGE_CMD[] = "change";
const char INTERRUPT_CMD[] = "interrupt";
const char RESUME_CMD[] = "resume";
const char PRINT_CMD[] = "print";
const char PRINTALL_CMD[] = "printall";
const char ENROLLIN_CMD[] = "enrollin";
const char ADDGRADE_CMD[] = "addgrade";
const char PROTOCOL_CMD[] = "protocol";
const char REPORT_CMD[] = "report";
const char SAVE_CMD[] = "save";
const char SAVEAS_CMD[] = "saveas";
const char HELP_CMD[] = "help";



/// <summary>
/// implementation of user interface, this is in charge of communigation between the user and class SUSI
/// </summary>
class UserInterface {
	/// <summary>
	/// here is the system SUSI
	/// </summary>
	SUSI system;
	template<typename T>
	/// <summary>
	/// deletes dynamically located data, sets the porinter to nullptr
	/// </summary>
	/// <typeparam name="T">template</typeparam>
	/// <param name="data">some data from the heap</param>
	void clear(T* data);
	/// <summary>
	/// checks if memory from heap is correctly located
	/// </summary>
	/// <typeparam name="T">template parameter</typeparam>
	/// <param name="data">some dynamic data</param>
	/// <returns>returns false if the memory has not located correctly, true otherwise</returns>
	template<typename T>
	bool memCheck(T* data);
	/// <summary>
	/// all the commands go in here to get identified and then call the desired functions
	/// </summary>
	/// <param name="command">takes a command</param>
	/// <returns>returns if the command controller is continuing to take command or not. if the command is CLOSE_CMD it returns false</returns>
	bool commandController(char command[]);
	/// <summary>
	/// enroll and the following functions call take some data from the console written by the user, and then passses it to SUSI to execure following commands
	/// </summary>
	void enroll();
	void advance();
	void change();
	void graduate();
	void interrupt();
	void resume();
	void print() const;
	void printall();
	void enrollin();
	void report() const;
	void addGrade();
	void protocol();
	void save() const;
	void saveAs() const;
	/// <summary>
	/// prints information about how to write commands properly
	/// </summary>
	void help() const;
public:
	/// <summary>
	/// takes a command from the user and passes it to the UserInterface::commandController()
	///when UserInterface::commandController() returns false, the cycle stops and the application closes
	/// </summary>
	void openCommandLine();
};

char* readStrSUSI(std::istream& in, bool hasSpaces, size_t size);

template<typename T>
inline void UserInterface::clear(T* data)
{
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

template<typename T>
inline bool UserInterface::memCheck(T* data)
{
	if (data == nullptr) {
		cout << "could not locate memory..." << endl;
		return false;
	}
	return true;
}

#endif
