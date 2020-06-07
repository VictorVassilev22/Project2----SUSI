#ifndef STUDENT_H
#define STUDENT_H
#include "Specialty.hpp"

///Max value for status. We have 3 options, only one of them is marked
const size_t STATUS_MAX = 3;
const size_t MAX_GROUP = 8;
const char DEF_STUDENT_NAME[10] = "anonymous";

const double MIN_GRADE = 2.0;
const double MIN_PASS_GRADE = 3.0;
const double MAX_GRADE = 6.0;

///Realization of Student class
///
///Stores needful information about the student.

class Student {
	friend class SUSI;
	///Student's personal name
	char* name;
	///Student's faculty number
	///by default it is 0 and this is invalid value for the application
	unsigned f_num;
	///Indicates what group the student has joined
	size_t group;
	///Indicates what year of university the student is studying
	unsigned year;
	/// Only one of the following elements is true (0 - joined, 1-interrupted, 2-graduated)
	bool status[STATUS_MAX];
	//Student's specialty
	Specialty specialty;
	///Elective subjects for that student
	bool electives[MAX_E_SUB] = { false, };
	///Elective subjects for that student
	bool required[MAX_R_SUB] = { false, };
	double required_grades[MAX_R_SUB] = { 0.0, };
	double elective_grades[MAX_E_SUB] = { 0.0, };
	///copies the values of Student::status to a new bool array
	void copyStatus(bool const src[]);
	///copies the values of Student::subjects to a new TakenSubject list
	//void copySubjects(TakenSubject const* src);
	///Help function used in copy constructors.
	void copy(Student const& other);
	///A template function which clears dynamically located data from heap of a random type object.
	template<typename T>
	void clear(T*& str);
	///Sets Student::name, deletes and allocates it's memory first.
	void setName(const char* other_name);
	///changes Sudent::group
	void changeGroup(size_t new_group);
	///Changes year. @returns false if year is not the next year.
	bool changeYear(unsigned new_year);
	/// @returns true if the subject is not taken, @returns true if the subject is taken and has grade >3.00
	bool checkIfPassed(unsigned subject, bool isRequired = true);
	bool isQualifiedForSpecialty(Specialty const& spec);
	/// <summary>
	/// copies required courses from the program to this Student::required[MAX_R_SUB]
	/// </summary>
	void copyRequired();
public:
	///Default constructor initializes Student with initial values. View source code.
	///@note We assume if Student::f_num is 0, there is no such Student.
	Student();
	Student(const char* name, unsigned f_num, size_t group, Specialty& sp, unsigned year = 1);
	///Copy constructor.
	///@see Student::copy()
	Student(Student const& other);
	///Deletes dynamically located memory reom the heap. (Student::name, Student::subjects)
	~Student();
	///Checks if this and other differ and if so, calls Student::copy().
	///@see Student::copy()
	Student& operator=(Student const& other);
	///@returns Student::f_num
	unsigned getFn()const { return f_num; }
	///@returns Student::year
	unsigned getYear()const { return year; }
	///@returns Student::group
	unsigned getGroup()const { return group; }
	///Sets Students::status true and position "index". Nullifies at all other positions.
	void setStatus(size_t index);
	//Checks if the student is interrupted
	bool hasInterrupted() const { return status[1]; }
	bool hasYearForCourse(unsigned sub, bool isRequired = true);
	///@returns the value of Student::name
	char* getName() const;
	///@returns the value of Student::specialty
	const Specialty& getSpecialty() const { return specialty; }
	/// <returns>the name of the program the student has taken</returns>
	char* getSpecName() const { return specialty.getName(); }
	/// <param name="i">index of the course</param>
	/// <returns>grade for that course, returns 0 if the course is not taken or does not exist, returns 2 if the course is taken, but exam is not attended yet </returns>
	double getGrade(unsigned i, bool isRequired = true) const;
	/// <summary>
	/// calculates the average grade of the student
	/// </summary>
	/// <returns>double</returns>
	double getAverageGrade() const;
	/// <summary>
	/// 0-studying 1-interrupted 2-graduated
	/// </summary>
	void printStatus() const;
	unsigned getStatus() const;
	void report() const;
	void print() const;
	bool enrollinElective(unsigned index);
	bool enrollinRequired(unsigned index);
	void addGrade(double grade, size_t subject, bool isRequired = true);
	bool hasRequired(unsigned sub) const { return required[sub]; }
	bool hasElective(unsigned sub) const { return electives[sub]; }
	/// <summary>
	/// prints protocol for that student given a course
	/// </summary>
	/// <param name="sub"></param>
	/// <param name="isRequired"></param>
	void printProtocolCourse(unsigned sub, bool isRequired = true) const;
};

#endif