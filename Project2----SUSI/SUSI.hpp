#ifndef SUSI_H
#define SUSI_H
#include "Student.hpp"
#include<iostream>
#include<fstream>

const size_t MAX_SPECS = 2;
const size_t MAX_PROG_SUBJECTS_R = 20;
const size_t MAX_PROG_SUBJECTS_E = 10;
const size_t MAX_YEARS = 4;
const size_t MAX_STUDENTS = 200;
const size_t MAX_FILENAME = 40;

/// names of the courses are shortened to ease the work{ "AG", "DIS1", "LA", "UP", "VA", "DS", "DIS2", "OOP", "AE1", "DUPR", "EAI", "IO", "SDP", "AE2", "DAA", "KA", "LP", "CHM", "KM", "OS", "VS", "FP", "BD",
///"GEOM", "AI", "MP", "SEP", "KG", "ST", "CHMDU", "TCH", "MA1", "DU", "DM1", "MA2", "DG", "LO", "AM", "KAN", "ML"};

/// <summary>
/// loading some data for the two programs: mathematics and informatics... for now
///this and the following indicate which subjects does each program have _e(_E) stands for elective, _r(_R) stands for required
/// </summary>
const unsigned informatics_subjects[MAX_PROG_SUBJECTS_R] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
const unsigned informatics_subjects_e[MAX_PROG_SUBJECTS_E] = {1,3,5,7,9,11,13,15,17,19};
const unsigned mathematics_subjects[MAX_PROG_SUBJECTS_R] = {0,1,2,3,4,5,6,9,12,30,31,32,33,34,35,36,37,38,20,21,};
const unsigned mathematics_subjects_e[MAX_PROG_SUBJECTS_E] = {0,2,4,6,8,10,12,14,16,18};

const char FILE_NAME[] = "file.txt";
/// <summary>
/// realization of SUSI class, the powrhouse of the application. Executes all commands.
/// </summary>
class SUSI {
	/// <summary>
	/// list of programs
	/// </summary>
	Specialty specialties[MAX_SPECS];
	/// <summary>
	/// list of students
	///basically an array for every year
	/// </summary>
	Student students[MAX_YEARS][MAX_STUDENTS];

	/// <summary>
	/// checks if a student with such fn alredy exists
	/// </summary>
	/// <param name="fn">desired fn</param>
	/// <returns>true if doeasnt exist</returns>
	bool isFnFree(unsigned fn) const;
	/// <summary>
	/// setting the data from the previously hardcoded arrays with the subjects. when adding more programs, firts add similar arrays for the 
	/// new programs, then change MAX_SPECS and then open this function and follow the example to load the new programs
	/// </summary>
	void setSpecialties();
	void addStudent(Student const& s, unsigned year = 1);
	/// <summary>
	/// sets the student back to default
	/// </summary>
	/// <param name="fn">desired fn</param>
	void removeStudent(unsigned fn);
	int getSpecialtyIndex(char const* name) const;
	Student getStudent(unsigned fn) const;
	int getStudent(unsigned fn, int& year) const;
	void swapStudents(size_t s1, size_t s2, const unsigned year);
	///implementing simple bubble sort from smaller to bigger fn
	void sortStudents(const unsigned year);
	/// <summary>
	/// saves students to a file
	/// </summary>
	/// <param name="filename">name of the file</param>
	void saveStudents(const char* filename = FILE_NAME) const;
	/// <summary>
	/// reads students from the file
	/// </summary>
	void loadStudents();
	/// <summary>
	/// reading one student from the file
	/// </summary>
	/// <param name="in">the stream</param>
	/// <param name="year">the year the student is currently in</param>
	/// <param name="s">the student is saved here</param>
	/// <returns>if the student has beed read successfuly or not</returns>
	bool readStudent(std::ifstream& in, unsigned year, Student& s);
	/// <summary>
	/// reads a symbol string
	/// </summary>
	/// <param name="in">the stream</param>
	/// <param name="hasSpaces">if the stream has spaces, if so reads until new line, if not, reads until space</param>
	/// <param name="size">the maximum size of the string</param>
	/// <returns></returns>
	char* readStrSUSI(std::istream& in, bool hasSpaces, size_t size) const;
	/// <summary>
	/// File format (the last symbols of the file name) must be .txt, if not the file is not accepted and the data is not saved
	/// </summary>
	/// <param name="filename">the name of the file</param>
	/// <returns>if the format is as desired or not</returns>
	bool checkTxtFileFormat(char const* filename) const;
public:
	/// <summary>
	/// calls SUSI::setSpecialties() and SUSI::loadStudents()
	/// </summary>
	/// <returns></returns>
	SUSI();
	///calls SUSI::loadStudents()
	~SUSI();
	/// <summary>
	/// enroll and the following functions are command that do as pointed in the paper
	/// </summary>
	/// <param name="f_num"></param>
	/// <param name="specialty_name"></param>
	/// <param name="group"></param>
	/// <param name="student_name"></param>
	void enroll(unsigned f_num, const char* specialty_name, size_t group, const char* student_name);
	void advance(unsigned f_num);
	void changeGroup(unsigned fn, size_t new_group);
	void changeSpecialty(unsigned fn, const char* spec);
	void changeYear(unsigned fn, unsigned year);
	void graduate(unsigned fn);
	void interrupt(unsigned fn);
	void resume(unsigned fn);
	void report(unsigned fn) const;
	void print(unsigned fn) const;
	void printAll(const char* name, unsigned year) const;
	void enrollin(unsigned fn, const char* subject);
	void addGrade(unsigned fn, const char* subject, double grade);
	/// <summary>
	/// calls SUSI::sortStudents(const unsigned year) and then prints the protocol for the course and year
	/// </summary>
	/// <param name="course"></param>
	/// <param name="program"></param>
	/// <param name="year"></param>
	void protocol(const char* course, const Specialty& program, const unsigned year);
	/// <summary>
	/// calls SUSI::protocol(const char* course, const Specialty& program, const unsigned year) for every program and every year
	/// </summary>
	/// <param name="course"></param>
	void protocolAll(const char* course);
	/// <summary>
	/// saves the currently loaded data in the file
	/// </summary>
	void save() const;
	/// <summary>
	/// saves the data in a file of desired name, however the program does not load from this file at start if not explicitly said
	/// </summary>
	void saveAs() const;
};

#endif