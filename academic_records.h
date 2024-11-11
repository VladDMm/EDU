//#pragma once
//#ifndef ACADEMIC_RECORDS
//#define ACADEMIC_RECORDS
//
//#include "IncludesCentral.h"
//
//
//class Administrator;
//class SystemManagement;
//class NotaDetaliata;
//class Absente;
//class AbsentaDetaliata;
//class Student;
//class Catedra;
//
//class DatabaseConnection
//{
//public:
//	DatabaseConnection();
//
//	~DatabaseConnection() 
//	{
//		if (conn) {
//			conn->close();
//		}
//	}
//
//	// Metodă pentru a executa un query
//	void executeQuery(const std::string &query);
//
//	std::vector<std::tuple<int, std::string, std::string, std::string, int>> selectStudents();
//
//	// Metodă pentru a executa un query de tip SELECT student
//	//std::vector<std::pair<int, std::string>> selectStudents(const std::string& query);
//
//	// Metodă pentru a executa un query de tip SELECT departments
//	std::vector<std::pair<int, std::string>> selectDepartments(const std::string& query);
//
//	void displayGroups_from_bd()const;
//
//	// Metodă pentru a actualiza catedra
//	void updateCatedra(int id, const std::string &newName);
//
//	void addGroupToDatabase(const std::string& groupName, int groupYear, int id_catedra);
//
//	// Metodă pentru a obține ultimul ID inserat
//	int getLastInsertId();
//	int getLastInsertId(const char *query);
//
//private:
//	sql::Driver *driver; 
//	std::unique_ptr<sql::Connection> conn;
//};
//
//class User
//{
//public:
//	User() = default;
//
//	enum UserType
//	{
//		admin,
//		student,
//		profesor
//	};
//
//	User (size_t id_user, const std::string &name, const std::string &email, const std::string &user, const std::string &pass, UserType type)
//		: id_user(id_user),full_name(name), email(email), username(user), password_hash(pass), user_type(type) {}
//
//	User(const std::string &name, const std::string &email, const std::string &user, const std::string &pass, UserType type)
//		: full_name(name), email(email), username(user), password_hash(pass), user_type(type) {}
//
//	virtual void show_menu() = 0;
//
//	std::string get_username()
//	{
//		return username;
//	}
//
//	std::string get_passw()
//	{
//		return password_hash;
//	}
//
//	virtual ~User() = default;
//
//protected:
//	unsigned int id_user;
//	UserType user_type;
//
//	std::string full_name;
//	std::string email;
//	std::string username;
//	std::string password_hash;
//	std::string salt;
//};
//
//class Student : public User
//{
//public:
//	// CTOR
//	Student() {}
//	
//	Student(size_t &id, const std::string& nume)
//		: id_student(id)/*, full_name(nume)*/ {}
//
//	Student(size_t &id, std::string& nume, std::string& email, size_t id_grupa, std::string &user, std::string &pass)
//		: id_student(id), group_id(id_grupa), User(id, nume, email, user, pass, UserType::student) {};
//
//	Student(std::string& nume, std::string& email, size_t id_grupa, std::string &user, std::string &pass)
//		: group_id(id_grupa), User(nume, email, user, pass, UserType::student) {};
//
//	// Suprascrierea operatorului <
//	bool operator<(const Student& other) const {
//		// Compară întâi după nume
//		if (full_name != other.full_name) {
//			return full_name < other.full_name;
//		}
//		// Dacă numele sunt egale, compară după ID
//		return id_student < other.id_student;
//	}
//
//	void insert_into_db() const;
//
//	// function
//	void show_menu() override;
//
//	// actualizeaza numele
//	void update_name();
//
//	// afisare informatii student
//	void display_student() const;
//
//	//static void displayAllStudents(DatabaseConnection& db_conn) {
//	//	auto students = db_conn.selectStudents();
//	//	std::cout << "ID\tFull Name\tEmail\t\tUsername\tGroup ID\n";
//	//	std::cout << "-----------------------------------------------------\n";
//	//	for (const auto& student : students) {
//	//		int student_id;
//	//		std::string fullname, email, username;
//	//		int group_id;
//
//	//		// Destructurează tuple-ul
//	//		std::tie(student_id, fullname, email, username, group_id) = student;
//
//	//		// Afișează informațiile
//	//		std::cout << student_id << "\t" << fullname << "\t" << email << "\t"
//	//			<< username << "\t" << group_id << "\n";
//	//	}
//	//}
//
//	// obtine id studentului
//	size_t get_id() const;
//
//	// obtine numele
//	std::string get_name() const;
//
//	~Student() override = default;
//private:
//	size_t id_student = 0;
//	size_t user_id = 0;
//	size_t group_id = 0;
//};
//
//class Profesor : public User
//{
//public:
//	Profesor() {}
//
//	Profesor(size_t id, const std::string &name, std::string &role)
//		: id_professor(id), full_name(name), professor_role(role) {}
//	
//	Profesor(size_t id, const std::string &name, const std::string &email, std::string &role, std::string &user, std::string &pass)
//		: id_professor(id), full_name(name), professor_role(role), User(id, name,email, user, pass, UserType::profesor) {}
//
//	Profesor(const std::string &name, const std::string &email, std::string &role, std::string &user, std::string &pass)
//		: full_name(name), professor_role(role), User(name, email, user, pass, UserType::profesor) {}
//
//	void show_menu() override;
//
//	size_t get_id_prof() const;
//
//	std::string get_full_name() const;
//
//	std::string get_role() const;
//
//	~Profesor() override = default;
//
//	void insert_into_db() const;
//
//
//private:
//	size_t id_professor = 0;
//	std::string full_name;
//	std::string professor_role;
//};
//
//class Grupa {
//public:
//	Grupa(){}
//
//	// Constructor to initialize group with ID, name, and year
//	Grupa(size_t id, const std::string& name, int year) :
//		id_group(id), group_name(name), year_of_study(year) {}
//	// Constructor to initialize group with students
//	//Grupa(std::vector<Student> &student_vector)
//	//{ students.insert(students.begin(), student_vector.begin(), student_vector.end()); }
//	
//	// Add students to the group
//	void add_student(std::vector<Student> &);
//	void add_student(std::map<size_t, Student>::iterator &);
//
//	// Display students in the group
//	void display_students_in_group() const;
//	void display_all_students() const;
//
//	// Remove a student by ID
//	void remove_student(size_t);
//
//	// Display group details
//	void display_group() const;
//
//	// Get the group ID
//	size_t get_id() const;
//
//	// Get a list of students in the group
//	const std::vector<Student> get_students() const;
//
//	// Get the number of students
//	size_t get_num_students() const;
//
//private:
//	size_t id_group;
//	std::string group_name;
//	int year_of_study;
//	std::vector<Student> students;
//};
//
//class Nota {
//public:
//	Nota() {}
//
//	Nota(const std::string& course) : course_name(course) {}
//
//	// Adaugă o notă pentru un student
//	void add_grade(std::string, Student& student, double);
//
//	// Calculează media notelor pentru un student
//	double calculate_average(const Student& student) const;
//
//	// Caută o notă specifică pentru un student
//	bool search_grade(const Student&, double) const;
//
//	// Afișează toate notele pentru toți studenții
//	void display_grades() const;
//
//private:
//	std::string course_name;  // Numele cursului pentru care se țin notele
//	std::map<Student, std::vector<NotaDetaliata>> grades;  // Map între student și notele sale detaliate
//};
//
//class NotaDetaliata {
//public:
//
//	NotaDetaliata(double value, const std::chrono::system_clock::time_point &date)
//		: value(value), date(date) {}
//
//	double get_value() const { return value; }
//
//	std::string get_date() const
//	{
//		std::time_t tt = std::chrono::system_clock::to_time_t(date);
//		std::stringstream ss;
//		ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
//		return ss.str();
//	}
//
//private:
//	double value;
//	std::chrono::system_clock::time_point date; // Data și ora adăugării notei
//};
//
//class Absente {
//public:
//	Absente() {}
//
//	Absente(const std::string &course_name) : course_name(course_name) {}
//
//	void add_absence(std::string &, const Student &, std::string &);
//
//	void remove_absence(const Student &);
//
//	void display_absence() const;
//
//private:
//	std::string course_name;  // Numele cursului pentru care se țin notele
//	std::map<Student, std::vector<AbsentaDetaliata>> absences;  // Map între student și notele sale detaliate
//
//};
//
//class AbsentaDetaliata {
//public:
//
//	AbsentaDetaliata(std::string reason, const std::chrono::system_clock::time_point &date)
//		: reason(reason), date(date)
//	{
//		++total_absences;
//	}
//
//	std::string get_reason() const { return reason; }
//
//	short get_total_absence() const { return total_absences; }
//
//	std::string get_date() const
//	{
//		std::time_t tt = std::chrono::system_clock::to_time_t(date);
//		std::stringstream ss;
//		ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
//		return ss.str();
//	}
//
//private:
//	size_t total_absences = 0;
//	std::string reason;
//	std::chrono::system_clock::time_point date; // Data și ora adăugării notei
//};
//
//class Curs {
//public:
//	Curs() {}
//	~Curs() {}
//
//	void insert_into_db() const;
//
//	// Constructor care inițializează un curs cu un ID și o denumire
//	Curs(size_t id, const std::string& name) :
//		id_course(id), course_name(name) {}
//	
//	// Constructor de copiere care primește un curs și un profesor
//	Curs(Curs& obj_curs, Profesor& prof)
//		: id_course(obj_curs.id_course), course_name(obj_curs.course_name)
//	{
//		course_professors.push_back(prof);
//	}
//
//	// Constructor care primește un student și îl adaugă la curs
//	Curs(const Student& obj_student)
//	{
//		course_students.push_back(obj_student);
//	}
//
//	// Get the course details
//	//Curs get_course() const;
//
//	 // Adaugă o notă pentru un student într-un curs
//	void add_grade_for_student(std::string, Student &, double);
//
//	// Display the course details(name)
//	void display_course() const;
//
//	// Display students in the course
//	void display_students_in_course() const;
//
//	// Add a professor to the course
//	void add_professor(Profesor &p_tmp);
//
//	// Adauga absenta pentru student. Parametri - nume curs; - obiect student; -absenta
//	void add_absence_for_student(std::string &, const Student &, std::string&);
//
//	// Add students to the course
//	void add_students(const std::vector<Student> &);
//
//	void add_single_student(const Student &);
//
//	// Display the professors of the course
//	void display_professors_in_course()const;
//
//	void display_students_absences() const;
//
//	void display_students_grades() const;
//
//	// Remove a student by ID
//	void remove_student(size_t id_student);
//
//	// Get the course ID
//	size_t get_id();
//
//	std::string get_name_course() {
//		return course_name;
//	}
//
//	// Get a vector of id students
//	std::vector<size_t> get_id_students() const;
//
//	// Get a vector of id professors
//	std::vector<size_t> get_id_professors() const;
//
//private:
//	size_t id_course;
//	std::string course_name;
//	std::vector<Student> course_students;
//	std::vector<Profesor> course_professors;
//	Nota nota; 
//	Absente absente;
//};
//
//class Catedra {
//public:
//	Catedra() {}
//	Catedra(size_t id, const std::string& name, const std::string &faculty)
//		: id_catedra(id), catedra_name(name), faculty(faculty) {}
//
//	void insert_catedra_to_bd();
//
//	// Add a new professor to the system
//	void add_professor();
//
//	// Add a professor to a course
//	void add_professor_to_course();
//
//	// Add students to a course
//	void add_students_to_course();
//
//	// Add a new group to the system
//	void add_group();
//
//	// Add students to a group
//	void add_students_to_group();
//
//	// Add a new course
//	void add_course();
//
//	void add_grade_to_course(size_t id_prof);
//
//	void add_absence_to_course(size_t);
//
//	void display_absence_in_course(size_t);
//
//	void display_grades_in_course(size_t) const;
//
//	// Display all students in the system
//	void display_students() const;
//
//	// Display students in a course
//	void display_students_in_course() const;
//
//	// Afisare studentii de la curs dupa cursurile care ii apartin profesorului
//	void display_students_in_course_by_prof(size_t) const;
//
//	// Display students in a group
//	void display_students_in_group() const;
//
//	// Display all professors
//	void display_professors() const;
//
//	// Display professors in a course
//	void display_professors_in_course() const;
//
//	// Display all groups
//	void display_groups() const;
//
//	// Afisare cursuri ale studentului dupa id-ul lui
//	void show_student_courses(size_t id) const;
//
//	// Afisarea cursurilor care ii apartine profesorului
//	void show_professor_courses(size_t) const;
//
//	// Obtine mapa cu studenti
//	const std::map<size_t, Student>& get_studenti() const {
//		return students;
//	}
//
//	// Obtine mapa cu profesori
//	const std::map<size_t, Profesor>& get_profesori() const {
//		return professors;
//	}
//
//	// Obtine id catedra;
//	size_t get_id() const {
//		return id_catedra;
//	}
//
//	// Obtine nume catedra
//	std::string get_name_catedra() const {
//		return catedra_name;
//	}
//	
//	// Verifică dacă un student este în această catedră
//	bool has_student(size_t id_student) const;
//
//	// Verifica daca un profesor este in aceasta catedra
//	bool has_professor(size_t id_profesor) const;
//
//	// Returneaza un obiect student, carui ii apartine user/pass-ul
//	Student* authenticate_student(std::string &user, std::string &pass);
//
//	Profesor* authenticate_profesor(std::string &user, std::string &pass);
//
//private:
//	size_t id_catedra;
//	std::string catedra_name;
//	std::string faculty;
//
//
//	std::vector<Curs> courses;
//	std::map<size_t, Student> students; // Lista de studenți
//	std::map<size_t, Profesor> professors; // Lista de profesori
//	std::map<size_t, Curs> course_prof_map; // Lista de cursuri cu profesori, studenti
//	std::map<size_t, Grupa> groups; // Lista de grupe cu studentii lor
//};
//
//// Clasa SystemManagement. Clasa gestionata de admin pentru a adauga date in catedra, si utilizata in Student/Profesor pentru a prelua instanta.
//class SystemManagement
//{
//public:
//	// Metoda statica pentru a obtine instanta Singleton
//	static SystemManagement* getInstance();
//
//	// Functia care returneaza o harta de catedre
//	std::map<size_t, Catedra> &get_catedre();
//
//	// Funcția care returnează catedra la care apartine un student
//	// pe baza unui id_student
//	const Catedra *get_catedra_student(size_t id_student);
//
//	// Funcția care returnează catedra la care apartine un profesor
//	// pe baza unui id_profesor
//	Catedra *get_catedra_profesor(size_t id_profesor);
//
//	//function for db
//	//void add_group();
//	void add_catedra();
//	void add_group_to_catedra();
//	void add_students_to_group();
//	void update_info_catedra();					// Redenumire catedra
//	void remove_catedra();
//	void display_students_from_db();
//
//
//	// function for variable
//	void display_students() const;				// Afisarea studentilor
//
//	//void add_students_to_catedra();
//	void add_professor_to_catedra();
//	void add_courses_to_catedra();
//
//	void add_students_to_course();
//	void add_professor_to_course();
//
//	void display_catedre() const;
//	
//	void display_students_in_course() const;	// Afisarea studentilor intr-un curs
//	void display_students_in_group() const;		// Afisarea studentilor dintr-un grup
//	void display_professors() const;			// Afisarea profesorilor
//	void display_professors_in_course() const;	// Afisarea profesorilor dintr-un curs
//	void display_groups() const;				// Afisarea grupelor
//
//	~SystemManagement() {
//		delete instance;
//	}
//
//private:
//	std::map<size_t, Catedra> catedre;
//
//	SystemManagement() {}
//	static SystemManagement* instance;
//};
//
//class Administrator : public User
//{
//public:
//	Administrator() {}
//
//	Administrator(SystemManagement *sistem) : sistem(SystemManagement::getInstance()) {}
//
//	Administrator(size_t id_user, std::string &name, const std::string &email, std::string &user, std::string &pass, SystemManagement *sistem) : User(id_user, name, email, user, pass, UserType::admin), sistem(SystemManagement::getInstance()) {}
//	
//	void show_menu() override;
//
//	// Funcție pentru crearea obiectului de tip User în funcție de rol
//	//std::unique_ptr<User> create_user(const std::string& user, const std::string& pass, const std::string& name, User::UserType type) {
//	//	switch (type) {
//	//	case User::UserType::student:
//	//		return std::make_unique<Student>(user, pass, name);
//	//	case User::UserType::profesor:
//	//		return std::make_unique<Profesor>(user, pass, name);
//	//	case User::UserType::admin:
//	//		return std::make_unique<Administrator>(user, pass, name);
//	//	default:
//	//		return nullptr;
//	//	}
//	//}
//
//	//Administrator* authenticate_admin(std::string &user, std::string &pass);
//
//	~Administrator() override = default;
//
//private:
//	SystemManagement *sistem;
//};
//
//#endif // !ACADEMIC_RECORDS
