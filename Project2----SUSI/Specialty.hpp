#ifndef SPECIATY_H
#define SPECIALTY_H
#include<cstring>
#include<iostream>

const size_t MAX_R_SUB = 40;
const size_t MAX_E_SUB = 20;
const size_t MAX_NAME = 40;
/// <summary>
/// the default constructor assignes the name of the program with this
/// </summary>
const char DEF_NAME[18] = "Default Specialty";

/// <summary>
/// here are all the names of the required courses
/// </summary>
const char all_required_subjects[MAX_R_SUB][MAX_NAME] = { "AG", "DIS1", "LA", "UP","VA", "DS", "DIS2", "OOP","AE1","DUPR","EAI","IO","SDP","AE2","DAA","KA","LP","CHM","KM","OS","VS","FP","BD",
"GEOM","AI","MP","SEP","KG","ST","CHMDU","TCH","MA1", "DU", "DM1", "MA2", "DG","LO","AM", "KAN", "ML"};

/// <summary>
/// indicates in which year you can take the desired course
/// </summary>
const unsigned year_to_take_rs[MAX_R_SUB] = { 1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,
	3,3,3,3,3,3,3,4,4,4,2,2,2,2,2,2,2,3,3,3};

/// <summary>
/// here are all the names of the elective courses
/// </summary>
const char all_elective_subjects[MAX_E_SUB][MAX_NAME] = { "I1","I2","I3","I4","I5","I6","I7","I8","I9","I10","I11","I12","I13","I14","I15","I16","I17","I18","I19","I20"};

/// <summary>
/// indicates in which year you can take the desired elective course
/// </summary>
const unsigned year_to_take_es[MAX_E_SUB] = { 1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4 };

class Specialty {
	/// <summary>
	/// name of the program
	/// </summary>
	char* name;
	/// <summary>
	/// all af the required courses
	/// </summary>
	bool required[MAX_R_SUB] = {false, };
	/// <summary>
	/// all of the elective courses
	/// </summary>
	bool electives[MAX_E_SUB] = {false, };
	/// <summary>
	/// setting the required courses for the program
	/// </summary>
	/// <param name="origin">contains the indexes of the courses for the program</param>
	/// <param name="size">the size of the array</param>
	void setRequired(const unsigned origin[], size_t size);
	/// <summary>
	/// setting the elective courses for the program
	/// </summary>
	/// <param name="origin">contains the indexes of the courses for the program</param>
	/// <param name="size">the size of the array</param>
	void setElectives(const unsigned origin[], size_t size);
	/// <summary>
	/// copies a string and sets this name to it
	/// </summary>
	/// <param name="other">the other passed name</param>
	void setName(char const* other);
	/// <summary>
	/// used by the copy constructor and operator = to copy data from other 
	/// </summary>
	/// <param name="other">the other program</param>
	void copy(Specialty const& other);
public:
	Specialty(char const* name, const unsigned required[], size_t size_r,  const unsigned electives[], size_t size_e);
	Specialty();
	Specialty(Specialty const& other);
	~Specialty();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="isRequired">if the course is required or elective</param>
	/// <param name="index">ithe index of the course</param>
	/// <returns>the year in which the course should be taken</returns>
	unsigned getSubjectYear(bool isRequired, size_t index) const;
	/// <summary>
	/// copies the name into another string
	/// </summary>
	/// <returns>the pointer to the copy, should get deleted every time after calling it</returns>
	char* getName() const;
	/// <summary>
	/// checks if the program has a desired subject
	/// </summary>
	/// <param name="sub">the index of the subject</param>
	/// <param name="isRequired">if the course is required or not</param>
	/// <returns>if the program has such course</returns>
	bool hasSubject(unsigned sub, bool isRequired = true) const;
	Specialty& operator=(Specialty const& other);
	/// <param name="i">the index</param>
	/// <param name="isRequired">if it is required</param>
	/// <returns>the name of the course</returns>
	const char* getSubjectName(size_t i, bool isRequired = true) const;
	/// <param name="name">by entered name</param>
	/// <returns>the index of the course / -1 if not found</returns>
	int getRequiredSubject(const char* name) const;
	/// <param name="name">by entered name</param>
	/// <returns>the index of the elective course / -1 if not found</returns>
	int getElectiveSubject(const char* name) const;
};

#endif