#include "IncludesCentral.h"

void SystemManagement::display_students_from_db()
{
	//std::string query = "SELECT user_id, full_name FROM users";
	auto students = db_conn.selectStudents();

	std::cout << "ID\tFull Name\tEmail\t\tUsername\tGroup ID\n";
	std::cout << "-----------------------------------------------------------------------\n";
	for (const auto& student : students) {
		int student_id;
		std::string fullname, email, username, password;
		int group_id;

		// Destructurează tuple-ul
		std::tie(student_id, fullname, email, username, group_id) = student;

		// Afișează informațiile
		std::cout << student_id << "\t\t" << fullname << "\t" << email << "\t"
			<< username << "\t\t\t" << group_id << "\n";
	}
}

void SystemManagement::display_catedre() const
{
	std::string query = "Select department_id, department_name FROM departments";

	std::vector<std::pair<int, std::string>> catedre = db_conn.selectDepartments(query);

	for (const auto &catedra : catedre)
		std::cout << "ID: " << catedra.first << ", " << catedra.second << std::endl;
}

void SystemManagement::add_catedra()
{
	system("cls");
	std::cin.ignore();
	std::cout << "Pentru sfarsit apasa enter" << std::endl;
	short id = 1;

	if (!catedre.empty())
	{
		id = (--catedre.end())->first;
		++id;
		do
		{
			std::cout << "Introdu nume catedra: ";
			std::string nume_catedra;
			std::getline(std::cin, nume_catedra);
			if (!nume_catedra.empty())
			{
				std::string faculty;
				std::cout << "Introdu facultatea: ";
				std::getline(std::cin, faculty);

				Catedra temp(id, nume_catedra, faculty);
				catedre[id] = temp;
				temp.insert_catedra_to_bd();
				++id;
			}
			else
				break;

		} while (true);
	}

	else
	{
		do
		{
			std::cout << "Introdu nume catedra: ";
			std::string nume_catedra;
			std::getline(std::cin, nume_catedra);
			if (!nume_catedra.empty())
			{
				std::string faculty;
				std::cout << "Introdu facultatea: ";
				std::getline(std::cin, faculty);

				Catedra temp(id, nume_catedra, faculty);
				catedre[id] = temp;
				temp.insert_catedra_to_bd();
				++id;
			}
			else
				break;

		} while (true);
	}


}

void SystemManagement::remove_catedra()
{
	system("cls");

	this->display_catedre();

	std::cout << "Introdu id catedra: ";
	int id_catedra;
	std::cin >> id_catedra;
	std::cin.ignore();

	std::string query = "DELETE FROM departments WHERE department_id = id_catedra";
	db_conn.executeQuery(query);

	auto catedra_it = catedre.find(id_catedra);
	if (catedra_it == catedre.end())
	{
		std::cout << "nu este asa catedra" << std::endl;
		return;
	}
	catedre.erase(catedra_it);
	std::cout << "catedra " << id_catedra << " a fost stearsa cu succes" << std::endl;
}

//
//void SystemManagement::display_catedre() const
//{
//	system("cls");
//	for (const auto catedra_entry : catedre)
//	{
//		std::cout << catedra_entry.first << ": " 
//			<< catedra_entry.second.get_name_catedra() << std::endl;
//	}
//}
// Implementare actualizare informatii catedra

void SystemManagement::update_info_catedra() {
	system("cls");

	this->display_catedre();

	size_t id;
	std::cout << "Introdu ID-ul catedrei pe care vrei sa o actualizezi: ";
	std::cin >> id;
	std::cin.ignore();

	auto it = catedre.find(id);
	if (it == catedre.end()) {
		std::cout << "Catedra nu exista!\n";
		return;
	}

	std::cout << "Introdu nume nou" << std::endl;
	std::string new_name;
	std::getline(std::cin, new_name);

	db_conn.updateCatedra(id, new_name);
}

//void SystemManagement::add_group()
//{
//	this->display_catedre();
//
//	unsigned short id_catedra;
//	std::cout << "Introdu ID-ul catedrei: ";
//	std::cin >> id_catedra;
//	auto it = catedre.find(id_catedra); // Caută catedra
//	if (it == catedre.end()) {
//		std::cout << "Catedra cu ID-ul " << id_catedra << " nu a fost găsită.\n";
//		return;
//	}
//	it->second.add_group();
//}

// nu folosita
void SystemManagement::add_group_to_catedra()
{
	for (const auto &x : catedre)
		std::cout << x.first << ": " <<
		x.second.get_name_catedra() << std::endl;
	unsigned short id_catedra;
	std::cout << "Introdu ID-ul catedrei: ";
	std::cin >> id_catedra;
	auto it = catedre.find(id_catedra); // Caută catedra
	if (it == catedre.end()) {
		std::cout << "Catedra cu ID-ul " << id_catedra << " nu a fost găsită.\n";
		return;
	}
	it->second.add_group();

}

//void SystemManagement::add_students_to_catedra()
//{
//	system("cls");
//
//	for (const auto &x : catedre)
//		std::cout << x.first << ": " <<
//		x.second.get_name_catedra() << std::endl;
//
//	std::cout << "Introdu id-ul catedra: ";
//	size_t catedra_id;
//	std::cin >> catedra_id;
//
//	auto it_catedra = catedre.find(catedra_id);
//	
//	if (it_catedra != catedre.end())
//	{
//		it_catedra->second.add_students_to_group();
//		std::cout << "Studenti adaugati cu succes" << std::endl;
//	}
//	
//}

void SystemManagement::add_professor_to_catedra()
{
	system("cls");

	for (const auto &x : catedre)
		std::cout << x.first << ": " <<
		x.second.get_name_catedra() << std::endl;

	std::cout << "Introdu id-ul catedra: ";
	size_t catedra_id;
	std::cin >> catedra_id;

	auto it_catedra = catedre.find(catedra_id);

	if (it_catedra != catedre.end())
	{
		it_catedra->second.add_professor();
		std::cout << "Profesori adaugati cu succes" << std::endl;
	}
}

void SystemManagement::add_courses_to_catedra()
{
	system("cls");

	for (const auto &x : catedre)
		std::cout << x.first << ": " <<
		x.second.get_name_catedra() << std::endl;

	std::cout << "Introdu id-ul catedra: ";
	size_t catedra_id;
	std::cin >> catedra_id;

	auto it_catedra = catedre.find(catedra_id);

	if (it_catedra != catedre.end())
	{
		it_catedra->second.add_course();
		std::cout << "Cursuri adaugate cu succes" << std::endl;
	}
}

void SystemManagement::add_students_to_group()
{
	/*system("cls");

	for (const auto &x : catedre)
		std::cout << x.first << ": " <<
		x.second.get_name_catedra() << std::endl;

	std::cout << "Introdu id-ul catedra: ";
	size_t catedra_id;
	std::cin >> catedra_id;

	auto it_catedra = catedre.find(catedra_id);

	if (it_catedra != catedre.end())
	{
		it_catedra->second.add_students_to_group();
		std::cout << "Studenti adaugati cu succes" << std::endl;
	}*/

	system("cls");

	for (const auto &x : catedre)
		std::cout << x.first << ": " <<
		x.second.get_name_catedra() << std::endl;

	std::cout << "Introdu id-ul catedra: ";
	size_t catedra_id;
	std::cin >> catedra_id;

	auto it_catedra = catedre.find(catedra_id);

	if (it_catedra != catedre.end())
	{
		it_catedra->second.add_students_to_group();
		std::cout << "Studenti adaugati cu succes" << std::endl;

	}
}

void SystemManagement::add_students_to_course()
{
	system("cls");

	for (const auto &x : catedre)
		std::cout << x.first << ": " <<
		x.second.get_name_catedra() << std::endl;

	std::cout << "Introdu id-ul catedra: ";
	size_t catedra_id;
	std::cin >> catedra_id;

	auto it_catedra = catedre.find(catedra_id);

	if (it_catedra != catedre.end())
	{
		it_catedra->second.add_students_to_course();
		std::cout << "Studenti adaugati cu succes" << std::endl;
	}
}

void SystemManagement::add_professor_to_course()
{
	system("cls");

	for (const auto &x : catedre)
		std::cout << x.first << ": " <<
		x.second.get_name_catedra() << std::endl;

	std::cout << "Introdu id-ul catedra: ";
	size_t catedra_id;
	std::cin >> catedra_id;

	auto it_catedra = catedre.find(catedra_id);

	if (it_catedra != catedre.end())
	{
		it_catedra->second.add_professor_to_course();
		std::cout << "Profesori adaugati cu succes" << std::endl;
	}
}

const Catedra* SystemManagement::get_catedra_student(size_t id_student)
{
	for (const auto& catedra_pair : catedre)
	{
		const Catedra& catedra = catedra_pair.second;
		if (catedra.has_student(id_student))
		{ // Verifică dacă studentul este în catedră
			return &catedra; // Returnează pointer către catedra găsită
		}
	}
	return nullptr; // Returneaza nullptr daca studentul nu este gasit in nicio catedra
}

Catedra* SystemManagement::get_catedra_profesor(size_t id_profesor)
{
	for (auto& catedra_pair : catedre)
	{
		Catedra& catedra = catedra_pair.second;
		if (catedra.has_professor(id_profesor))
		{ // Verifica dacă prof-ul este in catedra
			return &catedra; // Returneaza pointer catre catedra gasita
		}
	}
	return nullptr; // Returneaza nullptr daca studentul nu este gasit in nicio catedra
}

std::map<size_t, Catedra>& SystemManagement::get_catedre()
{
	return catedre;
}

SystemManagement* SystemManagement::getInstance() {
	if (instance == nullptr) {
		instance = new SystemManagement();
	}
	return instance;
}

void SystemManagement::display_students() const
{
	system("cls");
	for (const auto &pair : catedre)
		std::cout << pair.first << ": "
		<< pair.second.get_name_catedra();

	std::cout << "Alege catedra: ";
	short id_catedra;
	std::cin >> id_catedra;

	auto it_catedra = catedre.find(id_catedra);
	if (it_catedra == catedre.end())
	{
		std::cout << "Nu este asa catedra!";
	}

	it_catedra->second.display_students();
}

void SystemManagement::display_professors() const
{
	system("cls");

	for (const auto &pair : catedre)
		std::cout << pair.first << ": "
		<< pair.second.get_name_catedra();

	std::cout << "Alege catedra: ";
	short id_catedra;
	std::cin >> id_catedra;

	auto it_catedra = catedre.find(id_catedra);
	if (it_catedra == catedre.end())
	{
		std::cout << "Nu este asa catedra!";
	}

	it_catedra->second.display_professors();
}

void SystemManagement::display_students_in_group() const
{
	system("cls");

	for (const auto &pair : catedre)
		std::cout << pair.first << ": "
		<< pair.second.get_name_catedra();

	std::cout << "Alege catedra: ";
	short id_catedra;
	std::cin >> id_catedra;

	auto it_catedra = catedre.find(id_catedra);
	if (it_catedra == catedre.end())
	{
		std::cout << "Nu este asa catedra!";
	}

	it_catedra->second.display_students_in_group();
}

void SystemManagement::display_students_in_course() const
{
	system("cls");

	for (const auto &pair : catedre)
		std::cout << pair.first << ": "
		<< pair.second.get_name_catedra();

	std::cout << "Alege catedra: ";
	short id_catedra;
	std::cin >> id_catedra;

	auto it_catedra = catedre.find(id_catedra);
	if (it_catedra == catedre.end())
	{
		std::cout << "Nu este asa catedra!";
	}

	it_catedra->second.display_students_in_course();
}

void SystemManagement::display_professors_in_course() const
{
	system("cls");

	for (const auto &pair : catedre)
		std::cout << pair.first << ": "
		<< pair.second.get_name_catedra();

	std::cout << "Alege catedra: ";
	short id_catedra;
	std::cin >> id_catedra;

	auto it_catedra = catedre.find(id_catedra);
	if (it_catedra == catedre.end())
	{
		std::cout << "Nu este asa catedra!";
	}

	it_catedra->second.display_professors_in_course();
}

void SystemManagement::display_groups() const
{
	system("cls");

	for (const auto &pair : catedre)
		std::cout << pair.first << ": "
		<< pair.second.get_name_catedra();

	std::cout << "Alege catedra: ";
	short id_catedra;
	std::cin >> id_catedra;

	auto it_catedra = catedre.find(id_catedra);
	if (it_catedra == catedre.end())
	{
		std::cout << "Nu este asa catedra!";
	}

	it_catedra->second.display_groups();
}