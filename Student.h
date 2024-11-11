#pragma once
#ifndef STUDENT
#define STUDENT


class Student : public User
{
public:
	// CTOR
	Student() {}

	Student(size_t &id, const std::string& nume)
		: id_student(id)/*, full_name(nume)*/ {}

	Student(size_t &id, std::string& nume, std::string& email, size_t id_grupa, std::string &user, std::string &pass)
		: id_student(id), group_id(id_grupa), User(id, nume, email, user, pass, UserType::student) {};

	Student(std::string& nume, std::string& email, size_t id_grupa, std::string &user, std::string &pass)
		: group_id(id_grupa), User(nume, email, user, pass, UserType::student) {};

	// Suprascrierea operatorului <
	bool operator<(const Student& other) const {
		// Compară întâi după nume
		if (full_name != other.full_name) {
			return full_name < other.full_name;
		}
		// Dacă numele sunt egale, compară după ID
		return id_student < other.id_student;
	}

	void insert_into_db() const;

	// function
	void show_menu() override;

	// actualizeaza numele
	void update_name();

	// afisare informatii student
	void display_student() const;

	//static void displayAllStudents(DatabaseConnection& db_conn) {
	//	auto students = db_conn.selectStudents();
	//	std::cout << "ID\tFull Name\tEmail\t\tUsername\tGroup ID\n";
	//	std::cout << "-----------------------------------------------------\n";
	//	for (const auto& student : students) {
	//		int student_id;
	//		std::string fullname, email, username;
	//		int group_id;

	//		// Destructurează tuple-ul
	//		std::tie(student_id, fullname, email, username, group_id) = student;

	//		// Afișează informațiile
	//		std::cout << student_id << "\t" << fullname << "\t" << email << "\t"
	//			<< username << "\t" << group_id << "\n";
	//	}
	//}

	// obtine id studentului
	size_t get_id() const;

	// obtine numele
	std::string get_name() const;

	~Student() override = default;
private:
	size_t id_student = 0;
	size_t user_id = 0;
	size_t group_id = 0;
};

#endif // !STUDENT