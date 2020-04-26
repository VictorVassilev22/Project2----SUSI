#ifndef PROGRAM_H
#define PROGRAM_H
#include "Subject.hpp"

///Maximum symols Program::name should have
const size_t MAX_NAME = 20;
///Maximum subjects a Program shuld have
const size_t MAX_SUBJECTS = 60;
///maximum symbols the path to the file should have
const size_t MAX_FILE_PATH = 50;

///This strucs is used to bind subject and year. This way will be easier to see for which year the Subject is intended for.
struct SpecSubject {
	Subject sub;
	unsigned year;

	///Initializes a subject for year 1 with an empty(invalid) name.
	SpecSubject();
};

///Realization of Program class
///This class is intended to store info about a specefic Program of studying. It has Subjects and a name.
///It also has a variable to indicate the path to the file where the subjects will be stored.

class Program {
	///Program's name.
	char name[MAX_NAME];
	///Stores path to the file with the subjects.
	///@see MAX_FILE_PATH
	char path[MAX_FILE_PATH];
	///Array of subjects. Will get written from a file
	///@see Program::path
	SpecSubject subjects[MAX_SUBJECTS];

	/// Help function used to copy data from another Program to this.
	///@see Program::Program(Program const&) operator=()
	void copy(Program const& other);
	///Copies all subjects from
	///@param src to
	///@param dest
	void copySubjects(SpecSubject dest[], SpecSubject const src[]);
public:
	///Default constructor initializes both member variables with ""(invalid values)
	Program();
	///Constructor initializes member variables with hopefully valid values
	Program(const char name[], const char path[]);
	///Copy constructor 
	///@see Program::copy()
	Program(Program const&);
	///Operator = is copies data from other Program to this only if they are different (their address).
	Program& operator=(Program const&);
	///Copies Program::name in heap and returns the pointer of the copy.
	char* getName() const;
};

#endif