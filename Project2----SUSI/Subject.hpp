#ifndef SUBJECT_H
#define SUBJECT_H

///Indicates maximum symbols a Subject::name should have.
const size_t MAX_SUB_NAME = 20;

///Realization of Subject class
///This class stores information for a Subject - it's name and if it is obligatory. Some functionality.
///@see TakenSubject

class Subject {
	///Indicates the name of the Subject
	char name[MAX_SUB_NAME];
	///Indicates if a Subject is obligatory or not
	bool isObligatory;
	///Help function used in Subject::Subject(Subject& const) and Subject::operator=()
	void copy(Subject const&);
public:
	///Default constuctor initializes Subject with invalid variable "" for name
	Subject();
	///Contructor sets Subject::name and Subject::isObligatory
	Subject(const char name[], bool isObl = false);
	///Copy constructor
	///@see Subject::copy()
	Subject(Subject& const other);
	///Operator = copies with Subject::copy() if this and other are not the same
	Subject& operator=(Subject const& other);

};
#endif