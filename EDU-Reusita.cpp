#include "academic_records.h"

SystemManagement *SystemManagement::instance = nullptr;

int main() 
{
	SystemManagement *sistem = SystemManagement::getInstance();

	std::string user_default = "admin", pass_default = "admin";

	Administrator admin(user_default, pass_default, sistem);

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

		std::string user, pass;

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
			}
			break;
		case 2:
			std::cout << "Introduceti username: ";
			std::cin >> user;
			std::cout << "Introduceti parola: ";
			std::cin >> pass;
			std::cin.ignore();
			for (auto &catedra : sistem->get_catedre())
			{

				Profesor *profesor = catedra.second.authenticate_profesor(user, pass);
				if (profesor)
				{
					std::cout << "Logare reusita" << std::endl;
					profesor->show_menu();
					break;
				}
				std::cout << "Date incorecte" << std::endl;
			}
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


	return 0;
}
