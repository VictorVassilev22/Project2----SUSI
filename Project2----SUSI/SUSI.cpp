#include "SUSI.hpp"

bool SUSI::isFnFree(unsigned fn) const
{
	int year = -1;
	int index = getStudent(fn, year);

	if (index < 0)
		return true;
	else
		return false;
}

void SUSI::setSpecialties()
{
	specialties[0] = Specialty("Informatics", informatics_subjects,
		MAX_PROG_SUBJECTS_R, informatics_subjects_e, MAX_PROG_SUBJECTS_E);
	specialties[1] = Specialty("Mathematics", mathematics_subjects,
		MAX_PROG_SUBJECTS_R, mathematics_subjects_e, MAX_PROG_SUBJECTS_E);
}


void SUSI::addStudent(Student const& s, unsigned year)
{

	if (s.getFn() == 0)
		return;

	for (size_t i = 0; i < MAX_STUDENTS; i++)
	{
		if (students[year-1][i].getFn() == 0) {
			students[year-1][i] = s;
			std::cout << "Student successfuly added in year " << year << "!" << std::endl;
			return;
		}
	}
	Student grad_s;
	if (year == MAX_YEARS) {
		for (size_t i = 0; i < MAX_STUDENTS; i++)
		{
			grad_s = students[year - 1][i];
			if (grad_s.getStatus() == STATUS_MAX - 1) {
				removeStudent(grad_s.getFn());
				students[year - 1][i] = s;
				std::cout << "Student successfuly added in year " << year << "!" << std::endl;
				return;
			}
		}
	}

	std::cout << "There is no space for another student, try again next year :)" << std::endl;
}

void SUSI::removeStudent(unsigned fn)
{
	int year = -1;
	int index = getStudent(fn, year);
	if (year < 0 || index < 0) {
		std::cout << "Student with such faculty number was not found!" << std::endl;
		return;
	}
	students[year][index] = Student();
}

int SUSI::getSpecialtyIndex(char const* name) const
{
	Specialty s;
	char* curr_name;
	for (size_t i = 0; i < MAX_SPECS; i++)
	{
		s = specialties[i];
		curr_name = s.getName();
		if (strcmp(name, curr_name) == 0)
			return i;

	}
	delete[] curr_name;
	return -1;
}

Student SUSI::getStudent(unsigned fn) const
{
	Student s;
	for (size_t i = 0; i < MAX_YEARS; i++)
	{
		for (size_t j = 0; j < MAX_STUDENTS; j++)
		{
			s = students[i][j];
			if (s.getFn() == fn) {
				return s;
			}
		}
	}
	std::cout << "Student with such faculty number was not found!" << std::endl;
	return s;
}

int SUSI::getStudent(unsigned fn, int& year) const
{
	for (size_t i = 0; i < MAX_YEARS; i++)
	{
		for (size_t j = 0; j < MAX_STUDENTS; j++)
		{
			if (students[i][j].getFn() == fn) {
				year = i;
				return j;
			}
		}
	}
	return -1;
}

void SUSI::swapStudents(size_t s1, size_t s2, const unsigned year)
{
	Student temp = students[year][s1];
	students[year][s1] = students[year][s2];
	students[year][s2] = temp;
}

void SUSI::sortStudents(const unsigned year)
{
	bool isSorted = false;
	bool hasSwapped = false;
	unsigned fn_1 = 0;
	unsigned fn_2 = 0;

	while (!isSorted) {
		hasSwapped = false;
		for (size_t i = 0; i < MAX_STUDENTS-1; i++)
		{
			fn_1 = students[year][i].getFn();
			fn_2 = students[year][i+1].getFn();

			if (fn_1 == 0 && fn_2 == 0)
				break;

			if ((fn_1 > fn_2) && (fn_2 > 0)) {
				swapStudents(i, i+1, year);
				hasSwapped = true;
			}
		}
		if (hasSwapped == false)
			isSorted = true;
	}

}

void SUSI::saveStudents(const char* filename) const
{
	std::ofstream out(filename, std::ios::out | std::ios::trunc);
	Student s;
	unsigned fn = 0;
	//write data here
	for (size_t i = 0; i < MAX_YEARS; i++)
	{
		out <<'#'<< i << std::endl;
		for (size_t j = 0; j < MAX_STUDENTS; j++)
		{
			if (!out.good()) {
				std::cout << "File stream status is not good, interrupting! Students are not saved!" << std::endl;
				return;
			}

			s = students[i][j];
			fn = s.getFn();
			if (fn == 0)
				continue;
			out<<s.getName()<<std::endl<< fn << " " << s.getGroup() << " " << s.getStatus() << " " << s.getSpecName() << std::endl <<"r"<<std::endl;
			for (size_t k = 0; k < MAX_R_SUB; k++)
			{
				if (s.hasRequired(k)) {
					out << k << " " << s.getGrade(k) << std::endl;
				}
			}
			out << "e" << std::endl;
			for (size_t k = 0; k < MAX_E_SUB; k++)
			{
				if (s.hasElective(k)) {
					out << k << " " << s.getGrade(k, false) << std::endl;
				}
			}
		}
	}
}

char* SUSI::readStrSUSI(std::istream& in, bool hasSpaces, size_t size) const
{
	char break_symbol = hasSpaces ? '\n' : ' ';
	char* name = new(std::nothrow) char[size];
	if (!name) {
		std::cout << "Error locating memory for specialty name!" << std::endl;
		return nullptr;
	}

	if(in.peek()==' ')
		in.ignore(); // ignores space

	size_t i = 0;
	char ch = in.get();
	while (ch != break_symbol)
	{
		if (ch == '\n')
			break;

		name[i] = ch;
		i++;

		if (i >= size - 1) {
			std::cout << "Maximum symbols for name reached! This string might be shortened." << std::endl;
			break;
		}
		ch = in.get();
	}
	name[i] = '\0';
	return name;
}

bool SUSI::checkTxtFileFormat(char const* filename) const
{
	size_t len = strlen(filename);
	if (len <= 5)
		return false;

	return filename[len - 1] == 't' && filename[len - 2] == 'x' && filename[len - 3] == 't' && filename[len - 4] == '.';
}

void SUSI::loadStudents()
{
	std::ifstream in(FILE_NAME, std::ios::in);
	
	char ch;
	unsigned year = 0;
	size_t index = 0;
	Student s;

	for (size_t i = 0; i < MAX_YEARS; i++)
	{
		index = 0;
		if (!in.good()) {
			std::cout << "File stream went bad :( Data not loaded! Please try again!" << std::endl;
			return;
		}
		ch = in.get();
		if (ch != '#') {
			std::cout << "Error reading year! Data not loaded!" << std::endl;
			return;
		}
		in >> year;
		ch = in.peek();
		if (ch == '\n')
			in.ignore();
		ch = in.peek();
		while (ch != '#') {
			if (in.eof())
				return;

			if (!readStudent(in, year, s))
				return;

			students[year][index] = s;
			index++;
			if (in.peek() == '\n')
				in.ignore();
			ch = in.peek();
		}

	}
	std::cout << "Students loaded successfully!" << std::endl;
}

bool SUSI::readStudent(std::ifstream& in, unsigned year, Student& s)
{
	char ch;
	unsigned fn = 0;
	char* name = nullptr;
	char* spec_name = nullptr;
	unsigned group = 0;
	unsigned status = 0;
	Specialty prog;
	int spec_index = -1;
	unsigned sub_index = 0;
	double grade = 0.0;

	name = readStrSUSI(in, true, MAX_NAME);
	in >> fn;
	in >> group;
	in >> status;
	spec_name = readStrSUSI(in, true, MAX_NAME);
	spec_index = getSpecialtyIndex(spec_name);
	if (spec_index < 0) {
		std::cout << "Error finding program! Student not loaded!" << std::endl;
		return false;
	}
	prog = specialties[spec_index];
	s = Student(name, fn, group, prog, year+1);
	ch = in.get();
	if (ch != 'r') {
		std::cout << "Error reading grades! Student not loaded!" << std::endl;
		return false;
	}
	ch = in.peek();
	while (ch != 'e') {
		in >> sub_index;
		in >> grade;
		if(grade>=MIN_GRADE)
			s.addGrade(grade, sub_index);
		in.ignore();
		ch = in.peek();
	}
	ch = in.get();
	if (ch != 'e') {
		std::cout << "Error reading elective subjects grades! Student not loaded!" << std::endl;
		return false;
	}
	in.ignore(); //ignores new line
	ch = in.peek();
	while (ch >= '0' && ch <= '9') {
		in >> sub_index;
		in >> grade;
		s.enrollinElective(sub_index);
		if (grade >= MIN_GRADE)
			s.addGrade(grade, sub_index, false);
		in.ignore();
		ch = in.peek();
	}
	std::cout << "Student "<<fn<<" loaded!" << std::endl;
}

SUSI::SUSI()
{
	setSpecialties();
	loadStudents();
}

SUSI::~SUSI()
{
	saveStudents();
}

void SUSI::enroll(unsigned f_num, const char* specialty_name, size_t group, const char* student_name)
{
	if (!isFnFree(f_num)) {
		std::cout << "Student with this faculty number alrefy exixts, please try again!" << std::endl;
		return;
	}

	int specialty_index = getSpecialtyIndex(specialty_name);
	if (specialty_index < 0) {
		std::cout << "No such specialty exixts!" << std::endl;
		return;
	}
	Specialty spec = specialties[specialty_index];
	Student s(student_name, f_num, group, spec);
	addStudent(s);
}

void SUSI::advance(unsigned fn)
{
	Student s = getStudent(fn);

	if (s.getFn() == 0) {
		return;
	}

	unsigned curr_year = s.getYear();

	if (s.hasInterrupted()) {
		std::cout << "This student has interrupted his educational program and does not have any rights" << std::endl;
		return;
	}

	if (!s.changeYear(curr_year + 1)) {
		return;
	}
	removeStudent(fn);
	addStudent(s, s.getYear());

}

void SUSI::changeGroup(unsigned fn, size_t new_group)
{
	Student s;
	int year = -1;
	int index = getStudent(fn, year);

	if (year < 0 || index < 0) {
		std::cout << "Student withthis faculty number does not exist!" << std::endl;
		return;
	}

	s = students[year][index];

	
	if (s.hasInterrupted()) {
		std::cout << "This student has interrupted his educational program and does not have any rights" << std::endl;
		return;
	}
	students[year][index].changeGroup(new_group);
}

void SUSI::changeSpecialty(unsigned fn, const char* spec)
{
	if (spec == nullptr) {
		std::cout << "Invalid program" << std::endl;
		return;
	}

	bool specialtyFound = false;
	Specialty needed_spec;
	for (size_t i = 0; i < MAX_SPECS; i++)
	{
		needed_spec = specialties[i];
		if (strcmp(needed_spec.getName(), spec) == 0) {
			specialtyFound = true;
			break;
		}
	}

	if (!specialtyFound) {
		std::cout << "Specialty "<< spec <<" does not exist!" << std::endl;
	}

	Student s;
	int year = -1;
	int index = getStudent(fn, year);

	if (year < 0 || index < 0) {
		std::cout << "Student withthis faculty number does not exist!" << std::endl;
		return;
	}

	s = students[year][index];


	if (s.hasInterrupted()) {
		std::cout << "This student has interrupted his educational program and does not have any rights" << std::endl;
		return;
	}

	if (!s.isQualifiedForSpecialty(needed_spec)) {
		std::cout << "This student has not passed all the subjects for the desired program!" << std::endl;
		return;
	}

	students[year][index].specialty = needed_spec;
	std::cout << "Student swiched specialty to " << spec << std::endl;
}

void SUSI::changeYear(unsigned fn, unsigned year)
{
	Student s = getStudent(fn);

	if (!s.changeYear(year)) {
		return;
	}

	if (s.getFn() == 0) {
		std::cout << "Student with this faculty number does not exist!" << std::endl;
		return;
	}

	if (s.hasInterrupted()) {
		std::cout << "This student has interrupted his educational program and does not have any rights" << std::endl;
		return;
	}

	removeStudent(fn);
	addStudent(s, year);
}

void SUSI::graduate(unsigned fn)
{
	Student s = getStudent(fn);
	if (s.getFn() < 0) {
		std::cout << "Student with this faculty number does not exist!" << std::endl;
		return;
	}

	if (s.hasInterrupted()) {
		std::cout << "This student has interrupted his educational program and does not have any rights" << std::endl;
		return;
	}

	for (size_t i = 0; i < MAX_R_SUB; i++)
	{
		if (!s.checkIfPassed(i)) {
			std::cout << "The student has not passed all his subjects and cannot graduate!"<<std::endl;
			return;
		}
	}

	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		if (!s.checkIfPassed(i, false)) {
			std::cout << "The student has not passed all his subjects and cannot graduate!" << std::endl;
			return;
		}
	}
	
	int year = -1;
	int index = getStudent(fn, year);

	s = students[year][index];

	students[year][index].setStatus(2);
	std::cout << "Student with faculty number "<<fn<<" graduated successfully!" << std::endl;
}

void SUSI::interrupt(unsigned fn)
{
	Student s;
	int year = -1;
	int index = getStudent(fn, year);

	if (year < 0 || index < 0) {
		std::cout << "Student withthis faculty number does not exist!" << std::endl;
		return;
	}

	s = students[year][index];

	
	students[year][index].setStatus(1);
	std::cout << "Student with faculty number " << fn << " has interrupted his educational program!" << std::endl;
}

void SUSI::resume(unsigned fn)
{
	int year = -1;
	int index = getStudent(fn, year);

	if (year < 0 || index < 0) {
		std::cout << "Student withthis faculty number does not exist!" << std::endl;
		return;
	}
	
	students[year][index].setStatus(0);
	std::cout << "Student with faculty number " << fn << " has resumed his educational program!" << std::endl;
}

void SUSI::report(unsigned fn) const
{
	Student s = getStudent(fn);
	s.report();
}

void SUSI::print(unsigned fn) const
{
	Student s = getStudent(fn);
	s.print();
}

void SUSI::printAll(const char* name, unsigned year) const
{
	Student s;
	char* spec_name;
	for (size_t i = 0; i < MAX_STUDENTS; i++)
	{
		s = students[year-1][i];

		if (!s.getName())
			continue;

		spec_name = s.getSpecName();
		if (strcmp(spec_name, name) == 0)
			s.print();
	}
}

void SUSI::enrollin(unsigned fn, const char* subject)
{
	Specialty program;
	int subject_index = -1;
	bool isRequired = false;

	for (size_t i = 0; i < MAX_E_SUB; i++)
	{
		if (strcmp(all_elective_subjects[i], subject) == 0) {
			subject_index = i;
		}
	}

	if (subject_index < 0) {
		for (size_t i = 0; i < MAX_R_SUB; i++)
		{
			if (strcmp(all_required_subjects[i], subject) == 0) {
				subject_index = i;
				isRequired = true;
			}
		}

		if (subject_index < 0) {
			std::cout << "No such subject exists!" << std::endl;
			return;
		}
	}


	Student s;
	int year = -1;
	int index = getStudent(fn, year);

	if (year < 0 || index < 0) {
		std::cout << "Student withthis faculty number does not exist!" << std::endl;
		return;
	}

	bool successfuly = true;
	if(isRequired)
		successfuly = students[year][index].enrollinRequired(subject_index);
	else
		successfuly = students[year][index].enrollinElective(subject_index);

	if(successfuly)
		std::cout << "Course successfuly taken!" << std::endl;

}

void SUSI::addGrade(unsigned fn, const char* subject, double grade)
{
	int student_year = -1;
	int student_index = getStudent(fn, student_year);
	if (student_index < 0) {
		std::cout << "Student with this faculty number does not exist!" << std::endl;
		return;
	}
	Student s = students[student_year][student_index];

	if (s.hasInterrupted()) {
		std::cout << "Student with faculty number " << fn << " has interrupted his educational program and connot attend to exams!" << std::endl;
		return;
	}

	Specialty program = s.getSpecialty();
	int subject_index = program.getRequiredSubject(subject);
	if (subject_index >= 0) {
		if (s.hasRequired(subject_index)) {
			students[student_year][student_index].addGrade(grade, subject_index);
			std::cout << "Grade " << grade << " added!" << std::endl;
			return;
		}
	}

	subject_index = program.getElectiveSubject(subject);
	if (subject_index < 0) {
		std::cout << "No such subject found!" << std::endl;
		return;
	}

	if (s.hasElective(subject_index)) {
		students[student_year][student_index].addGrade(grade, subject_index, false);
		std::cout << "Grade " << grade << " added!" << std::endl;
	}
	else {
		std::cout << "This course is not taken!" << std::endl;
	}

}

void SUSI::protocol(const char* course, const Specialty& program, const unsigned year)
{
	bool isRequired = true;
	int course_index = program.getRequiredSubject(course);

	if (course_index < 0)
		isRequired = false;

	if (!isRequired)
		course_index = program.getElectiveSubject(course);

	if (course_index < 0) {
		std::cout << "This course does not exist!" << std::endl;
		return;
	}

	sortStudents(year);
	bool hasCourse = false;
	Student s;
	for (size_t i = 0; i < MAX_STUDENTS; i++)
	{
		s = students[year][i];

		if (s.getFn() == 0)
			break;

		if (strcmp(s.getSpecialty().getName(), program.getName())==0) {
			hasCourse = isRequired ? s.hasRequired(course_index) : s.hasElective(course_index);
			if (hasCourse) {
				s.printProtocolCourse(course_index, isRequired);
			}
		}
	}
}

void SUSI::protocolAll(const char* course)
{
	for (size_t i = 0; i < MAX_SPECS; i++)
	{
		for (size_t j = 0; j < MAX_YEARS; j++)
		{
			protocol(course, specialties[i], j);
		}
	}
}

void SUSI::save() const
{
	saveStudents();
}

void SUSI::saveAs() const
{
	char* filename = readStrSUSI(std::cin, false, MAX_FILENAME);
	if (!checkTxtFileFormat(filename)) {
		std::cout << "Invalid file format, file must be in .txt format and at least 5 symbols long!" << std::endl;
		return;
	}
	saveStudents(filename);
}
