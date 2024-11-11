#include "IncludesCentral.h"

void Administrator::show_menu()
{
	short option;
	do
	{
		std::cout << "1. Adauga catedra" << std::endl;
		std::cout << "2. Adauga grupa la catedra" << std::endl;
		std::cout << "-. " << std::endl;
		std::cout << "4. Adauga profesori la catedra" << std::endl;
		std::cout << "5. Adauga curs la catedra" << std::endl;
		std::cout << "6. Adauga studenti la grupa" << std::endl;
		std::cout << "7. Adauga studenti la curs" << std::endl;
		std::cout << "8. Adauga profesori la curs" << std::endl;
		std::cout << "9. Afiseaza catedre" << std::endl;
		std::cout << "10. Sterge catedra" << std::endl;
		std::cout << "11. Afisaeza toti studentii" << std::endl;
		std::cout << "12. Afisaeza grupele" << std::endl;
		std::cout << "0. Iesi" << std::endl;
		std::cout << "Alege optiunea: " << std::endl;
		std::cin >> option;

		switch (option)
		{
		case 1:
			sistem->add_catedra();
			system("cls");
			break;
		case 2:
			sistem->add_group_to_catedra();
			system("cls");
			break;
		case 3:
			//sistem->add_students_to_catedra();
			system("cls");
			break;
		case 4:
			sistem->add_professor_to_catedra();
			system("cls");
			break;
		case 5:
			sistem->add_courses_to_catedra();
			system("cls");
			break;
		case 6:
			sistem->add_students_to_group();
			system("cls");
			break;
		case 7:
			sistem->add_students_to_course();
			system("cls");
			break;
		case 8:
			sistem->add_professor_to_course();
			system("cls");
			break;
		case 9:
			sistem->display_catedre();
			system("cls");
			break;
		case 10:
			sistem->remove_catedra();
			system("cls");
			break;
		case 11:
			sistem->display_students_from_db();
			break;
		case 12:
			sistem->display_groups();
			break;
		case 0:
			system("cls");
			std::cout << "La revedere!" << std::endl;
			break;
		default:
			system("cls");
			std::cout << "Nu este asa optiune!" << std::endl;
			break;
		}

	} while (option != 0);

}