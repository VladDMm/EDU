#pragma once
#ifndef ACADEMIC_RECORDS
#define ACADEMIC_RECORDS

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <mariadb/conncpp.hpp>
#include <memory>

#include <utility>  // for std::pair
#include <chrono>   // for std::chrono::system_clock
#include <iomanip>  // for std::put_time
#include <sstream>  // for std::stringstream

class Administrator;
class SystemManagement;
class NotaDetaliata;
class Absente;
class AbsentaDetaliata;

class DatabaseConnection {
public:
	DatabaseConnection() {

		// Configurare conexiune
		sql::SQLString url("jdbc:mariadb://localhost:3306/academic_records");
		sql::Properties properties({ {"user", "root"}, {"password", "root"} });

		// Conectează la baza de date
		try {
			driver = sql::mariadb::get_driver_instance();  // Obține driverul MariaDB
			conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
			std::cout << "Conexiune reușită!" << std::endl;
		}
		catch (sql::SQLException &e) {
			std::cerr << "Eroare de conexiune: " << e.what() << std::endl;
		}
	}

	~DatabaseConnection() 
	{
		conn->close();
	}

	// Metodă pentru a executa un query
	void executeQuery(const std::string &query) {
		try {
			std::unique_ptr<sql::Statement> stmt(conn->createStatement());
			stmt->execute(query);
		}
		catch (sql::SQLException &e) {
			std::cerr << "Query failed: " << query << std::endl;
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}

private:
	sql::Driver *driver;  // Modificat tipul pentru driver
	std::unique_ptr<sql::Connection> conn;
};


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

	// Suprascrierea operatorului <
	bool operator<(const Student& other) const {
		// Compară întâi după nume
		if (full_name != other.full_name) {
			return full_name < other.full_name;
		}
		// Dacă numele sunt egale, compară după ID
		return id_student < other.id_student;
	}
	/*void insert_user_into_db(DatabaseConnection& db_conn, const std::string& username, const std::string& password) {
		std::string query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')";
		db_conn.executeQuery(query);
	}

	void insert_student_into_db(DatabaseConnection& db_conn, size_t id, const std::string& full_name, const std::string& username) {
		std::string query = "INSERT INTO students (id, full_name, username) VALUES (" +
			std::to_string(id) + ", '" + full_name + "', '" + username + "')";
		db_conn.executeQuery(query);
	}*/
	void insert_into_db(DatabaseConnection &db_conn) const {
		// Inserare în tabela users
		std::string user_query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')";
		db_conn.executeQuery(user_query);

		// Inserare în tabela students
		std::string student_query = "INSERT INTO students (id ,full_name, username, password) VALUES ('" +
			std::to_string(id_student) + "', '" + full_name + "', '" + username + "', '" + password + "')";
		db_conn.executeQuery(student_query);
	}

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

	void show_menu() override;

	size_t get_id_prof() const;

	std::string get_full_name() const;

	std::string get_role() const;

	~Profesor() override = default;

	void insert_into_db(DatabaseConnection &db_conn) const {
		// Inserare în tabela users
		std::string user_query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')";
		db_conn.executeQuery(user_query);

		// Inserare în tabela professors
		std::string professor_query = "INSERT INTO professors (id, full_name, professor_role, username, password) VALUES ('" +
			std::to_string(id_professor) + "', '" + full_name + "', '" + professor_role + "', '" + username + "', '" + password + "')";
		db_conn.executeQuery(professor_query);
	}



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
	Nota() {}

	Nota(const std::string& course) : course_name(course) {}

	// Adaugă o notă pentru un student
	void add_grade(std::string, Student& student, double);

	// Calculează media notelor pentru un student
	double calculate_average(const Student& student) const;

	// Caută o notă specifică pentru un student
	bool search_grade(const Student&, double) const;

	// Afișează toate notele pentru toți studenții
	void display_grades() const;

private:
	std::string course_name;  // Numele cursului pentru care se țin notele
	std::map<Student, std::vector<NotaDetaliata>> grades;  // Map între student și notele sale detaliate
};

class NotaDetaliata {
public:

	NotaDetaliata(double value, const std::chrono::system_clock::time_point &date)
		: value(value), date(date) {}

	double get_value() const { return value; }

	std::string get_date() const
	{
		std::time_t tt = std::chrono::system_clock::to_time_t(date);
		std::stringstream ss;
		ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
		return ss.str();
	}

private:
	double value;
	std::chrono::system_clock::time_point date; // Data și ora adăugării notei
};

class Absente {
public:
	Absente() {}

	Absente(const std::string &course_name) : course_name(course_name) {}

	void add_absence(std::string &, const Student &, std::string &);

	void remove_absence(const Student &);

	void display_absence() const;

private:
	std::string course_name;  // Numele cursului pentru care se țin notele
	std::map<Student, std::vector<AbsentaDetaliata>> absences;  // Map între student și notele sale detaliate

};

class AbsentaDetaliata {
public:

	AbsentaDetaliata(std::string reason, const std::chrono::system_clock::time_point &date)
		: reason(reason), date(date)
	{
		++total_absences;
	}

	std::string get_reason() const { return reason; }

	short get_total_absence() const { return total_absences; }

	std::string get_date() const
	{
		std::time_t tt = std::chrono::system_clock::to_time_t(date);
		std::stringstream ss;
		ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
		return ss.str();
	}

private:
	size_t total_absences = 0;
	std::string reason;
	std::chrono::system_clock::time_point date; // Data și ora adăugării notei
};

class Curs {
public:
	Curs() {}
	~Curs() {}

	void insert_into_db(DatabaseConnection &db_conn) const {
		std::string query = "INSERT INTO courses (id, course_name) VALUES (" +
			std::to_string(id_course) + ", '" + course_name + "')";
		db_conn.executeQuery(query);
	}

	void add_professor_to_db(DatabaseConnection &db_conn, const Profesor &prof) const {
		std::string query = "INSERT INTO professors_course (course_id, professor_id) VALUES (" +
			std::to_string(id_course) + ", " + std::to_string(prof.get_id_prof()) + ")";
		db_conn.executeQuery(query);
	}

	void add_student_to_db(DatabaseConnection &db_conn, const Student &student) const {
		std::string query = "INSERT INTO students_course (course_id, student_id) VALUES (" +
			std::to_string(id_course) + ", " + std::to_string(student.get_id()) + ")";
		db_conn.executeQuery(query);
	}


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
	//Curs get_course() const;

	 // Adaugă o notă pentru un student într-un curs
	void add_grade_for_student(std::string, Student &, double);

	// Display the course details(name)
	void display_course() const;

	// Display students in the course
	void display_students_in_course() const;

	// Add a professor to the course
	void add_professor(Profesor &p_tmp);

	// Adauga absenta pentru student. Parametri - nume curs; - obiect student; -absenta
	void add_absence_for_student(std::string &, const Student &, std::string&);

	// Add students to the course
	void add_students(const std::vector<Student> &);

	void add_single_student(const Student &);

	// Display the professors of the course
	void display_professors_in_course()const;

	void display_students_absences() const;

	void display_students_grades() const;

	// Remove a student by ID
	void remove_student(size_t id_student);

	// Get the course ID
	size_t get_id();

	std::string get_name_course() {
		return course_name;
	}

	// Get a vector of id students
	std::vector<size_t> get_id_students() const;

	// Get a vector of id professors
	std::vector<size_t> get_id_professors() const;

private:
	size_t id_course;
	std::string course_name;
	std::vector<Student> course_students;
	std::vector<Profesor> course_professors;
	Nota nota; 
	Absente absente;
};

class Catedra {
public:
	Catedra() {}
	Catedra(size_t id, const std::string& name)
		: id_catedra(id), catedra_name(name) {}

	// Add a new student to the system
	void add_students(DatabaseConnection &db_conn);

	// Add a new professor to the system
	void add_professor(DatabaseConnection &db_conn);

	// Add a professor to a course
	void add_professor_to_course();

	// Add students to a course
	void add_students_to_course();

	// Add a new group to the system
	void add_group();

	// Add students to a group
	void add_students_to_group();

	// Add a new course
	void add_course(DatabaseConnection &db_conn);

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

	std::vector<Curs> courses;
	std::map<size_t, Student> students; // Lista de studenți
	std::map<size_t, Profesor> professors; // Lista de profesori
	std::map<size_t, Curs> course_prof_map; // Lista de cursuri cu profesori, studenti
	std::map<size_t, Grupa> groups; // Lista de grupe cu studentii lor
};

// Clasa SystemManagement. Clasa gestionata de admin pentru a adauga date in catedra, si utilizata in Student/Profesor pentru a prelua instanta.
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

	void add_catedra();
	void display_catedre() const;
	void add_group_to_catedra();
	void remove_catedra();

	void add_students_to_catedra(DatabaseConnection& db_conn);
	void add_professor_to_catedra(DatabaseConnection& db_conn);
	void add_courses_to_catedra(DatabaseConnection& db_conn);

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
