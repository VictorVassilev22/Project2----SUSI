#ifndef SUBJECT_H
#define SUBJECT_H

const size_t MAX_SUB_NAME = 20;

class Subject {
	char name[MAX_SUB_NAME];
	bool isObligatory;

	void copy(Subject const&);
public:
	Subject();
	Subject(const char name[], bool isObl = false);
	Subject(Subject& const other);
	Subject& operator=(Subject const& other);

};
#endif