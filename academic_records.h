#pragma once
#ifndef ACADEMIC_RECORDS
#define ACADEMIC_RECORDS

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

class Profesor;

class User
{
	User(const std::string user, const std::string pass) : username(user), password(pass) {}
	virtual void show_menu() = 0;

	std::string get_username()
	{
		return username;
	}

	std::string get_passw()
	{
		return password;
	}

	virtual ~User() = default;
private:

	std::string username;
	std::string password;
};

class Student
{
public:
	Student() {}
	Student(size_t id, const std::string& nume)
		: id_student(id), full_name(nume) {}
	
	// actualizeaza numele
	void update_name();
	// afisare informatii student
	void display_student() const;
	// obtine id studentului
	size_t get_id() const;
	// obtine numele
	std::string get_name() const;

private:
	size_t id_student;
	std::string full_name;
};

class Grupa {
public:
	Grupa(){}
	// Constructor to initialize group with ID, name, and year
	Grupa(size_t id, const std::string& name, int year) :
		id_group(id), group_name(name), year_of_study(year) {}
	// Constructor to initialize group with students
	Grupa(std::vector<Student> &student_vector)
	{ students.insert(students.begin(), student_vector.begin(), student_vector.end()); }
	
	// Add students to the group
	void add_student(std::vector<Student> &);
	// Display students in the group
	void display_students_in_group() const;
	void display_all_students() const;
	// Remove a student by ID
	void remove_student(size_t);
	// Display group details
	void display_group() const;
	// Get the group ID
	size_t get_id() const;
	// Get a list of students in the group
	const std::vector<Student> get_students() const;
	// Get the number of students
	size_t get_num_students() const;

private:
	size_t id_group;
	std::string group_name;
	int year_of_study;
	std::vector<Student> students;
};

class Nota {
public:
	Nota() = default;

	std::vector<double>& get_note();
	void add_grade(double n);
	// Calculate the average grade
	double calculate_average() const;
	// Search for a specific grade
	void search_grade(double grade_to_search) const;
	// Display all grades
	void display_grades() const;

private:
	std::vector<double> grades;
};

class Curs {
public:
	Curs() {}
	~Curs() {}
	// Constructor care inițializează un curs cu un ID și o denumire
	Curs(size_t id, const std::string& name) :
		id_course(id), course_name(name) {}

	// Constructor de copiere care primește un curs și un profesor
	Curs(Curs& obj_curs, Profesor& prof)
		: id_course(obj_curs.id_course), course_name(obj_curs.course_name)
	{
		course_professors.push_back(prof);
	}

	// Constructor care primește un student și îl adaugă la curs
	Curs(const Student& obj_student)
	{
		course_students.push_back(obj_student);
	}

	// Get the course details
	Curs get_course() const;

	// Display the course details
	void display_course() const;

	// Display students in the course
	void display_students_in_course() const;

	// Add a professor to the course
	void add_professor(Profesor &p_tmp);

	// Add students to the course
	void add_students(const std::vector<Student> &);
	void add_single_student(const Student &);

	// Display the professors of the course
	void display_professors_in_course()const;

	// Remove a student by ID
	void remove_student(size_t id_student);

	// Get the course ID
	size_t get_id();

	// Get a list of students in the course
	std::vector<Student> get_students() const;

private:
	size_t id_course;
	std::string course_name;
	std::vector<Student> course_students;
	std::vector<Profesor> course_professors;
};

class Absente {
public:
	Absente(const std::string& date, const std::string& reason)
		: absence_date(date), absence_reason(reason), total_absences(1) {}

	void add_absence();

	void remove_absence();

	void display_absence() const;

private:
	std::vector<Student> absent_students;
	std::string absence_date;
	std::string absence_reason;
	size_t total_absences = 0;
};

class Profesor
{
public:
	Profesor() {}
	Profesor(size_t id, const std::string& name, std::string& role)
		: id_professor(id), full_name(name), professor_role(role) {}

	void add_grades() {
		// Funcționalitate pentru adăugarea notelor
		std::cout << "Adăugare note pentru profesorul " << full_name << "\n";
		// Aici ar trebui să fie implementată logica pentru adăugarea notelor
	}

	void view_students() const {
		// Funcționalitate pentru vizualizarea studenților
		std::cout << "Vizualizare studenți pentru profesorul " << full_name << "\n";
		// Aici ar trebui să fie implementată logica pentru vizualizarea studenților
	}

	size_t get_id()const;
	std::string get_full_name() const;
	std::string get_role() const;

private:
	size_t id_professor;
	std::string full_name;
	std::string professor_role;
};

class Catedra {
public:
	Catedra() {}
	Catedra(const std::string& name)
		: catedra_name(name) {}

	void display_catedre() const;
	// Add a new student to the system
	void add_students();
	// Add a new professor to the system
	void add_professor();
	// Add a professor to a course
	void add_professor_to_course();
	// Add students to a course
	void add_students_to_course();
	// Add a new group to the system
	void add_group();
	// Add students to a group
	void add_students_to_group();
	// Add a new course
	void add_course();
	// Display all students in the system
	void display_students() const;
	// Display students in a course
	void display_students_in_course() const;
	// Display students in a group
	void display_students_in_group() const;
	// Display all professors
	void display_professors() const;
	// Display professors in a course
	void display_professors_in_course() const;
	// Display all groups
	void display_groups() const;

private:
	std::string catedra_name;

	std::vector<Student> students;

	std::vector<Profesor> professors;
	std::vector<Curs> courses;

	std::map<size_t, Curs> course_prof_map;
	std::map<size_t, Grupa> groups;
};

// Clasa SystemManagement
class SystemManagement {
public:

	// Metodă statică pentru a obține instanța Singleton
	static SystemManagement* getInstance() {
		if (instance == nullptr) {
			instance = new SystemManagement();
		}
		return instance;
	}

	void add_catedra();
	void display_catedre() const;
	void add_group_to_catedra();
	void remove_catedra();

	void add_students_to_catedra();
	void add_professor_to_catedra();
	void add_courses_to_catedra();

	void add_students_to_group();
	void add_students_to_course();
	void add_professor_to_course();

	// Destructor pentru a curăța memoria
	~SystemManagement() {
		delete instance;
	}

private:
	SystemManagement() {}
	static SystemManagement* instance;
	std::map<size_t, Catedra> catedre;
};



#endif // !ACADEMIC_RECORDS
