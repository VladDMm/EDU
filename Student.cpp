#include "IncludesCentral.h"

void Student::update_name()
{
	std::string new_name;
	std::cout << "Introdu numele nou: ";
	std::getline(std::cin, new_name);
	full_name = new_name;
}

void Student::display_student() const
{
	std::cout << "Nume: " << full_name;
}

size_t Student::get_id() const
{
	return id_student;
}

std::string Student::get_name() const
{
	return full_name;
}

//void Student::insert_into_db() const {
//	// Inserare în tabela users
//	std::string user_query = "INSERT INTO users (fullname, email, username, password_hash, salt, user_type) VALUES ('" + full_name + "', '" + email + "', '" + username + "', '" + password_hash + "', '" + salt + "', '" + std::to_string(user_type) + "')";
//	db_conn.executeQuery(user_query);
//
//	// Inserare în tabela students
//	std::string student_query = "INSERT INTO students (user_id, group_id) VALUES ('" + std::to_string(user_id) + "', '" + std::to_string(group_id) + "')";
//	db_conn.executeQuery(student_query);
//}

void Student::insert_into_db() const {
	// Inserare în tabela users
	std::string user_query = "INSERT INTO users (fullname, email, username, password_hash, salt, user_type) "
		"VALUES ('" + full_name + "', '" + email + "', '" + username + "', '" + password_hash + "', '" + salt + "', 'student')";
	db_conn.executeQuery(user_query);

	// Obține ID-ul generat automat pentru user
	int new_user_id = db_conn.getLastInsertId("SELECT LAST_INSERT_ID() FROM `users`"); // Presupunând că există o metodă care obține `LAST_INSERT_ID()`

	// Asigură-te că `new_user_id` este valid
	if (new_user_id > 0)
	{
		// Inserare în tabela students
		std::string student_query = "INSERT INTO students (user_id, group_id) VALUES (" + std::to_string(new_user_id) + ", " + std::to_string(group_id) + ")";
		db_conn.executeQuery(student_query);
	}
	else {
		std::cerr << "Eroare: nu s-a putut obține user_id-ul generat pentru user." << std::endl;
	}
}

void Student::show_menu()
{
	// Obține instanța SystemManagement
	SystemManagement *system = SystemManagement::getInstance();
	// Apelează get_catedra_student pentru a obține catedra studentului curent
	const Catedra* catedra = system->get_catedra_student(id_student);

	short option;

	do
	{
		std::cout << "1. Afisare cursuri la care esti inscris" << std::endl;
		std::cout << "2. Afisare note" << std::endl;
		std::cout << "3. Afisare absente" << std::endl;
		std::cout << "0. Iesire" << std::endl;

		std::cin >> option;

		switch (option)
		{
		case 1:
		{
			if (!catedra)
			{
				std::cout << "Nu esti înscris la nicio catedră.\n";
				break;
			}
			std::cout << "Afisare cursuri inscrise pentru catedra: " << catedra->get_name_catedra() << "\n";
			catedra->show_student_courses(id_student);
		}
		break;
		case 2:
		{


		}
		break;
		case 3:
		{

		}
		break;
		case 0:
			break;
		default:
			break;
		}

	} while (option != 0);

}
