#ifndef STUDENT_H
#define STUDENT_H
#include"Program.hpp"

///Max value for status. We have 3 options, only one of them is marked
const size_t STATUS_MAX = 3;
///Default capacity of Student::subjects, there are goint to be resizing themselves.
const unsigned DEF_CAPACITY = 8;

///This struct is used to store the subjects a student would take.
struct TakenSubject {
	///A Subject
	Subject sub;
	///If the student has taken the exam or not.
	bool exam;
	/// The grade student achieved for this subject after he/she ha taken the exam.
	double grade;

	///This default constructor is needed and it assigns a default Subject to TakenSubject::sub, false to TakenSubject::exam,
	///and 0.0 to TakenSubject::grade
	TakenSubject();
};

///Realization of Student class
///
///Stores needful information about the student.

class Student {
	///Student's personal name
	char* name;
	///Student's faculty number
	unsigned f_num;
	///Indicates what group the student has joined
	size_t group;
	///Indicates what year of university the student is studying
	unsigned year;
	/// Only one of the following elements is true (0 - joined, 1-interrupted, 2-graduated)
	bool status[STATUS_MAX];
	///Avarege grade of all taken exams
	double avarege_grade;
	///All subjects the student has taken ever.
	TakenSubject* subjects;
	///Capacity of Student::subjects
	size_t subjects_capacity;
	///current count of elements of Student::subjects
	size_t subjects_size;

	///copies the values of Student::status to a new bool array
	void copyStatus(bool const src[]);
	///copies the values of Student::subjects to a new TakenSubject list
	void copySubjects(TakenSubject const* src);
	///Help function used in copy constructors.
	void copy(Student const& other);
	///A template function which clears dynamically located data from heap of a random type object.
	template<typename T>
	void clear(T* str);
	///Sets Student::name, deletes and allocates it's memory first.
	void setName(const char* other_name);
public:
	///Default constructor initializes Student with initial values. View source code.
	///@note We assume if Student::f_num is 0, there is no such Student.
	Student();
	Student(char* name, unsigned f_num, unsigned group, unsigned year = 1);
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
	///@returns the value of Student::name
	char* getName() const;
};

#endif