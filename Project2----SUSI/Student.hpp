#ifndef STUDENT_H
#define STUDENT_H
#include"Program.hpp"
const size_t STATUS_MAX = 3;
const unsigned DEF_CAPACITY = 8;

struct TakenSubject {
	Subject sub;
	bool exam;
	double grade;

	TakenSubject();
};

class Student {
	char* name;
	unsigned f_num;
	size_t group;
	unsigned year;
	bool status[STATUS_MAX]; //0-zapisan, 1-prekusnat, 2-zavurshil
	double avarege_grade;
	TakenSubject* subjects;
	size_t subjects_capacity;
	size_t subjects_size;

	void copyStatus(bool const src[]);
	void copySubjects(TakenSubject const* src);
	void copy(Student const& other);
	template<typename T>
	void clear(T* str);
	void setName(const char* other_name);
public:
	Student();
	Student(char* name, unsigned f_num, unsigned group, unsigned year = 1);
	Student(Student const& other);
	~Student();
	Student& operator=(Student const& other);
	unsigned getFn()const { return f_num; }
	unsigned getYear()const { return year; }
	unsigned getGroup()const { return group; }
	void setStatus(size_t index);
	char* getName() const;
};

#endif