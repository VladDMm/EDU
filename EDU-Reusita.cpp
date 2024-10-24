#include "academic_records.h"

SystemManagement *SystemManagement::instance = nullptr;

int main() {
	SystemManagement *sistem = SystemManagement::getInstance();

	std::string user = "admin1", pass = "pass1";

	Administrator admin(user, pass, sistem);

	Profesor profesor;
	
	short option;
	do
	{
		std::cout << "1. Student" << std::endl;
		std::cout << "2. Profesor" << std::endl;
		std::cout << "3. Administrator" << std::endl;
		std::cout << "0. Iesire" << std::endl;
		std::cout << "Alege optiune: ";
		std::cin >> option;
		
		switch (option)
		{
		case 1:
			// Logarea studentului
			std::cout << "Introduceti username: ";
			std::cin >> user;
			std::cout << "Introduceti parola: ";
			std::cin >> pass;
			std::cin.ignore();
			for (auto &catedra : sistem->get_catedre())
			{
				
				Student *student = catedra.second.authenticate_student(user, pass);
				if (student)
				{
					std::cout << "Logare reusita" << std::endl;
					student->show_menu();
					break;
				}
				std::cout << "Date incorecte" << std::endl;
				break;
			}
		case 2:
			profesor.show_menu();
			break;
		case 3:
			admin.show_menu();
			break;
		case 0:
			break;
		default:
			break;
		}

	} while (option != 0);

	/*do
	{
		Menu();
		std::cout << "Alege o optiune" << std::endl;
		std::cin >> option;

		switch (option)
		{
		case 1:
			sistem->add_catedra();
			break;
		case 2:
			sistem->add_group_to_catedra();
			break;
		case 3:
			sistem->add_students_to_catedra();
			break;
		case 4:
			sistem->add_professor_to_catedra();
			break;
		case 5:
			sistem->add_courses_to_catedra();
			break;
		case 6:
			sistem->add_students_to_group();
			break;
		case 7:
			sistem->add_students_to_course();
			break;
		case 8:
			sistem->add_professor_to_course();
			break;
		case 9:
			sistem->display_catedre();
			break;
		case 10:
			sistem->remove_catedra();
			break;
		case 0:
			std::cout << "La revedere!" << std::endl;
			break;
		default:
			std::cout << "Nu este asa optiune!" << std::endl;
			break;
		}
		
	} while (option != 0);*/

	return 0;
}
