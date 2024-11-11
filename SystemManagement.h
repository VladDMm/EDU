#pragma once
#ifndef SYSTEMANAGMENT
#define SYSTEMMANAGMENT

class SystemManagement
{
public:
	// Metoda statica pentru a obtine instanta Singleton
	static SystemManagement* getInstance();

	// Functia care returneaza o harta de catedre
	std::map<size_t, Catedra> &get_catedre();

	// Funcția care returnează catedra la care apartine un student
	// pe baza unui id_student
	const Catedra *get_catedra_student(size_t id_student);

	// Funcția care returnează catedra la care apartine un profesor
	// pe baza unui id_profesor
	Catedra *get_catedra_profesor(size_t id_profesor);

	//function for db
	//void add_group();
	void add_catedra();
	void add_group_to_catedra();
	void add_students_to_group();
	void update_info_catedra();					// Redenumire catedra
	void remove_catedra();
	void display_students_from_db();


	// function for variable
	void display_students() const;				// Afisarea studentilor

	//void add_students_to_catedra();
	void add_professor_to_catedra();
	void add_courses_to_catedra();

	void add_students_to_course();
	void add_professor_to_course();

	void display_catedre() const;

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

#endif // !SYSTEMANAGMENT

