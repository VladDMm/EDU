#pragma once
#ifndef ACADEMIC_RECORDS
#define ACADEMIC_RECORDS

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Administrator;
class SystemManagement;

class User
{
public:
	User() = default;
	User (std::string &user, std::string &pass) : username(user), password(pass) {}
	
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

protected:
	std::string username;
	std::string password;
};

class Student : public User
{
public:
	// CTOR
	Student() {}

	Student(std::string &user, std::string &pass) : User(user, pass) {};
	
	Student(size_t &id, const std::string& nume)
		: id_student(id), full_name(nume) {}

	Student(size_t &id, std::string& nume, std::string &user, std::string &pass)
		: id_student(id), full_name(nume), User(user, pass) {};

	// function
	void show_menu() override;
	// actualizeaza numele
	void update_name();
	// afisare informatii student
	void display_student() const;
	// obtine id studentului
	size_t get_id() const;
	// obtine numele
	std::string get_name() const;
	~Student() override = default;
private:
	size_t id_student;
	std::string full_name;
	
};

class Profesor : public User
{
public:
	Profesor() {}
	Profesor(std::string &user, std::string &pass) : User(user, pass) {}

	Profesor(size_t id, const std::string &name, std::string &role)
		: id_professor(id), full_name(name), professor_role(role) {}
	
	Profesor(size_t id, const std::string &name, std::string &role, std::string &user, std::string &pass)
		: id_professor(id), full_name(name), professor_role(role), User(user, pass) {}

	void add_grades() {
	}

	void view_students() const {
	}

	void show_menu() override;

	size_t get_id()const;
	std::string get_full_name() const;
	std::string get_role() const;

	~Profesor() override = default;

private:
	size_t id_professor;
	std::string full_name;
	std::string professor_role;
};

class Grupa {
public:
	Grupa(){}
	// Constructor to initialize group with ID, name, and year
	Grupa(size_t id, const std::string& name, int year) :
		id_group(id), group_name(name), year_of_study(year) {}
	// Constructor to initialize group with students
	//Grupa(std::vector<Student> &student_vector)
	//{ students.insert(students.begin(), student_vector.begin(), student_vector.end()); }
	
	// Add students to the group
	void add_student(std::vector<Student> &);
	void add_student(std::map<size_t, Student>::iterator &);
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
	//std::map<size_t, Student> students;
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

	// get a list of students in the course
	std::vector<Student> get_students() const;
	// get a vector of id students
	std::vector<size_t> get_id_students() const;
	

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
	std::string absence_date;
	std::string absence_reason;
	size_t total_absences = 0;
};

class Catedra {
public:
	Catedra() {}
	Catedra(size_t id, const std::string& name)
		: id_catedra(id), catedra_name(name) {}

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
	//
	void show_student_courses(size_t id) const;

	const std::map<size_t, Student>& get_studenti() const {
		return students;
	}

	const std::map<size_t, Profesor>& get_profesori() const {
		return professors;
	}

	size_t get_id() const {
		return id_catedra;
	}

	std::string get_nume_catedra() const {
		return catedra_name;
	}
	
	// Verifică dacă un student este în această catedră
	bool has_student(size_t id_student) const {
		return students.find(id_student) != students.end();
	}

	Student* authenticate_student(std::string &user, std::string &pass);

private:
	size_t id_catedra;
	std::string catedra_name;

	std::vector<Curs> courses;

	std::map<size_t, Student> students; // Lista de studenți
	std::map<size_t, Profesor> professors; // Lista de profesori
	std::map<size_t, Curs> course_prof_map;
	std::map<size_t, Grupa> groups;
};

// Clasa SystemManagement
class SystemManagement
{
public:
	// Metoda statica pentru a obtine instanta Singleton
	static SystemManagement* getInstance();
	// Functia care returneaza o harta de catedre
	std::map<size_t, Catedra> &get_catedre();
	// Funcția care returnează catedra la care apartine un student
	// pe baza unui id_student
	const Catedra* get_catedra_student(size_t id_student);

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

	void update_info_catedra();					// Redenumire catedra

	void display_students() const;				// Afisarea studentilor
	void display_students_in_course() const;	// Afisarea studentilor intr-un curs
	void display_students_in_group() const;		// Afisarea studentilor dintr-un grup
	void display_professors() const;			// Afisarea profesorilor
	void display_professors_in_course() const;	// Afisarea profesorilor dintr-un curs
	void display_groups() const;				// Afisarea grupelor

	~SystemManagement() {
		delete instance;
	}

private:
	std::map<size_t, Catedra> catedre;

	SystemManagement() {}
	static SystemManagement* instance;
};

class Administrator : public User
{
public:
	Administrator() {}

	Administrator(SystemManagement *sistem) : sistem(SystemManagement::getInstance()) {}

	Administrator(std::string &user, std::string &pass) : User(user, pass) {}

	Administrator(std::string &user, std::string &pass, SystemManagement *sistem) : User(user, pass), sistem(SystemManagement::getInstance()) {}
	
	void show_menu() override;

	~Administrator() override = default;

private:
	SystemManagement *sistem;
};

#endif // !ACADEMIC_RECORDS
