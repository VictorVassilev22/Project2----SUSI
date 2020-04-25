#ifndef PROGRAM_H
#define PROGRAM_H
#include "Subject.hpp"

const size_t MAX_NAME = 20;
const size_t MAX_SUBJECTS = 60;
const size_t MAX_FILE_PATH = 50;

struct SpecSubject {
	Subject sub;
	unsigned year;

	SpecSubject();
};

class Program {
	char name[MAX_NAME];
	char path[MAX_FILE_PATH];
	SpecSubject subjects[MAX_SUBJECTS];

	void copy(Program const& other);
	void copySubjects(SpecSubject dest[], SpecSubject const src[]);
public:
	Program();
	Program(const char name[], const char path[]);
	Program(Program const&);
	Program& operator=(Program const&);
	char* getName() const;
};

#endif