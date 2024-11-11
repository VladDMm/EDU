#pragma once
#ifndef CATEDRA
#define CATEDRA

class Catedra {
public:
	Catedra() {}
	Catedra(size_t id, const std::string& name, const std::string &faculty)
		: id_catedra(id), catedra_name(name), faculty(faculty) {}

	void insert_catedra_to_bd();

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

	void add_grade_to_course(size_t id_prof);

	void add_absence_to_course(size_t);

	void display_absence_in_course(size_t);

	void display_grades_in_course(size_t) const;

	// Display all students in the system
	void display_students() const;

	// Display students in a course
	void display_students_in_course() const;

	// Afisare studentii de la curs dupa cursurile care ii apartin profesorului
	void display_students_in_course_by_prof(size_t) const;

	// Display students in a group
	void display_students_in_group() const;

	// Display all professors
	void display_professors() const;

	// Display professors in a course
	void display_professors_in_course() const;

	// Display all groups
	void display_groups() const;

	// Afisare cursuri ale studentului dupa id-ul lui
	void show_student_courses(size_t id) const;

	// Afisarea cursurilor care ii apartine profesorului
	void show_professor_courses(size_t) const;

	// Obtine mapa cu studenti
	const std::map<size_t, Student>& get_studenti() const {
		return students;
	}

	// Obtine mapa cu profesori
	const std::map<size_t, Profesor>& get_profesori() const {
		return professors;
	}

	// Obtine id catedra;
	size_t get_id() const {
		return id_catedra;
	}

	// Obtine nume catedra
	std::string get_name_catedra() const {
		return catedra_name;
	}

	// Verifică dacă un student este în această catedră
	bool has_student(size_t id_student) const;

	// Verifica daca un profesor este in aceasta catedra
	bool has_professor(size_t id_profesor) const;

	// Returneaza un obiect student, carui ii apartine user/pass-ul
	Student* authenticate_student(std::string &user, std::string &pass);

	Profesor* authenticate_profesor(std::string &user, std::string &pass);

private:
	size_t id_catedra;
	std::string catedra_name;
	std::string faculty;


	std::vector<Curs> courses;
	std::map<size_t, Student> students; // Lista de studenți
	std::map<size_t, Profesor> professors; // Lista de profesori
	std::map<size_t, Curs> course_prof_map; // Lista de cursuri cu profesori, studenti
	std::map<size_t, Grupa> groups; // Lista de grupe cu studentii lor
};

#endif // !CATEDRA


