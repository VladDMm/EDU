#include "academic_records.h"

//void Menu()
//{
//	std::cout << "1. Adauga catedra" << std::endl;
//	std::cout << "2. Adauga grupa la catedra" << std::endl;
//	std::cout << "3. Adauga studenti la catedra" << std::endl;
//	std::cout << "4. Adauga profesori la catedra" << std::endl;
//	std::cout << "5. Adauga curs la catedra" << std::endl;
//	std::cout << "6. Adauga studenti la grupa" << std::endl;
//	std::cout << "7. Adauga studenti la curs" << std::endl;
//	std::cout << "8. Adauga profesori la curs" << std::endl;
//	std::cout << "9. Afiseaza catedre" << std::endl;
//	std::cout << "10. Sterge catedra" << std::endl;
//	std::cout << "0. Iesi" << std::endl;
//
//}

SystemManagement *SystemManagement::instance = nullptr;

int main() {
	SystemManagement *sistem = SystemManagement::getInstance();

	std::string user = "admin1", pass = "pass1";

	Administrator admin(user, pass, sistem);
	admin.show_menu();
	short option;
	
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
