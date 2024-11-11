#include "IncludesCentral.h"


void Profesor::show_menu()
{
	SystemManagement *system = SystemManagement::getInstance();

	// Apelează get_catedra_profesor pentru a obtine catedra profesorului curent
	Catedra *catedra = system->get_catedra_profesor(id_professor);

	if (!catedra)
	{
		std::cout << "Nu esti inscris la nici o catedra" << std::endl;
		return;
	}

	short option;
	do
	{
		std::cout << "1. Afisare cursuri disponibile" << std::endl;
		std::cout << "2. Afisare studenti la curs" << std::endl;
		std::cout << "3. Adauga nota la curs" << std::endl;
		std::cout << "4. Adauga absenta la curs" << std::endl;
		std::cout << "5. Afisare note la curs" << std::endl;
		std::cout << "6. Afisare absente la curs" << std::endl;
		std::cout << "0. Iesi" << std::endl;

		std::cin >> option;
		std::cin.ignore();

		switch (option)
		{
		case 1:
		{
			catedra->show_professor_courses(id_professor);
			break;
		}
		case 2:
		{
			catedra->display_students_in_course_by_prof(id_professor);
			break;
		}
		case 3:
		{
			catedra->add_grade_to_course(id_professor);
			break;
		}
		case 4:
		{
			catedra->add_absence_to_course(id_professor);
			break;
		}
		case 5:
			catedra->display_grades_in_course(id_professor);
			break;
		case 6:
			catedra->display_absence_in_course(id_professor);
		case 0:
			break;
		default:
			std::cout << "Alegere incorecta!" << std::endl;
			break;
		}
	} while (option != 0);

}

std::string Profesor::get_full_name() const
{
	return full_name;
}

size_t Profesor::get_id_prof()const
{
	return id_professor;
}

std::string Profesor::get_role() const
{
	return professor_role;
}

void Profesor::insert_into_db() const {
	//// Inserare în tabela users
	//std::string user_query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password_hash + "')";
	//db_conn.executeQuery(user_query);
	//// Inserare în tabela professors
	//std::string professor_query = "INSERT INTO professors (id, full_name, professor_role, username, password) VALUES ('" +
	//	std::to_string(id_professor) + "', '" + full_name + "', '" + professor_role + "', '" + username + "', '" + password_hash + "')";
	//db_conn.executeQuery(professor_query);

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
		std::string prof_query = "INSERT INTO professors (user_id, department_id) VALUES (" + std::to_string(new_user_id) + ", " + std::to_string(catedra_id) + ")";
		db_conn.executeQuery(prof_query);
	}
	else {
		std::cerr << "Eroare: nu s-a putut obține user_id-ul generat pentru user." << std::endl;
	}
}
