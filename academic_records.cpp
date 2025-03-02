﻿#include "academic_records.h"
#include <vector>

/*------------------------Class Administrator---------------------------------*/



/*----------------------End Class Administrator-----------------------------------*/

/*------------------------Class Student---------------------------------*/

void Student::update_name()
{
	std::string new_name;
	std::cout << "Introdu numele nou: ";
	std::getline(std::cin, new_name);
	full_name = new_name;
}

void Student::display_student() const
{
	std::cout << "ID: " << id_student << ", Nume: " << full_name;
}

size_t Student::get_id() const
{
	return id_student;
}

std::string Student::get_name() const 
{
	return full_name;
}

/*----------------------End Class Student-----------------------------------*/

/*----------------------Class Profesor-----------------------------------*/

std::string Profesor::get_full_name() const
{
	return full_name;
}

size_t Profesor::get_id()const
{
	return id_professor;
}

std::string Profesor::get_role() const
{
	return professor_role;
}

/*------------------------End Class Profesor---------------------------------*/

/*----------------------Class Grupa-----------------------------------*/

void Grupa::add_student(std::vector<Student> &student_vector)
{
	students.insert(students.begin(), student_vector.begin(), student_vector.end());
}

void Grupa::remove_student(size_t student_id)
{
	students.erase(std::remove_if(students.begin(), students.end(),
		[student_id](const Student& student) 
	{ return student.get_id() == student_id; }), students.end());
}

void Grupa::display_group() const 
{
	std::cout <<"Grupa: " << group_name << " (Anul " << year_of_study << ")";
}

void Grupa::display_all_students() const
{
	for (const auto &x : students)
	{
		std::cout << x.get_name() << std::endl;
	}
}

void Grupa::display_students_in_group() const
{
	std::cout << id_group <<": Grupa " << group_name << " (Anul " << year_of_study << ")\n";
	for (const auto &x : students)
	{
		std::cout << x.get_name() << std::endl;
	}
}

size_t Grupa::get_num_students() const
{
	return students.size();
}

size_t Grupa::get_id() const
{
	return id_group;
}

const std::vector<Student> Grupa::get_students() const
{
	return students;
}

/*--------------------------End Class Grupa-------------------------------*/

/*---------------------------Class Nota-----------------------------------*/

std::vector<double>& Nota::get_note() 
{
	return grades;
}

void Nota::add_grade(double n)
{
	grades.push_back(n);
}

double Nota::calculate_average() const
{
	if (grades.empty()) return 0.0;
	double suma = 0;
	for (double n : grades) {
		suma += n;
	}
	return suma / grades.size();
}

void Nota::search_grade(double grade_to_search) const
{
	if (std::find(grades.begin(), grades.end(), grade_to_search) != grades.end()) {
		std::cout << "Nota " << grade_to_search << " gasita.\n";
	}
	else {
		std::cout << "Nota " << grade_to_search << " nu exista.\n";
	}
}

void Nota::display_grades() const
{
	std::cout << "Note: ";
	for (double n : grades) {
		std::cout << n << " ";
	}
	std::cout << std::endl;
}

/*-------------------------End Class Nota--------------------------------*/

/*-------------------------Class Curs--------------------------------*/

Curs Curs::get_course() const
{
	return Curs(id_course, course_name);
}

void Curs::add_students(const std::vector<Student> &student_list)
{
	course_students.insert(course_students.begin(), student_list.begin(), student_list.end());
}

void Curs::add_single_student(const Student &new_student)
{
	course_students.push_back(new_student);
}

void Curs::remove_student(size_t id_student)
{
	course_students.erase(std::remove_if(course_students.begin(), course_students.end(),
		[id_student](const Student& student) { return student.get_id() == id_student; }), course_students.end());
}

void Curs::display_students_in_course()const
{
	if (course_students.empty())
	{
		std::cout << "Nu sunt studenti!\n";
		return;
	}
	for (const auto &x : course_students)
	{
		x.display_student();
	}
}

void Curs::display_professors_in_course()const
{
	for (const auto &x : course_professors)
		std::cout << x.get_id() << ": " << x.get_full_name() 
		<< " (" << x.get_role() << ")" << std::endl;
}

void Curs::display_course() const
{
	std::cout <<" Curs: " << course_name << "\n";
}

std::vector<Student> Curs::get_students() const
{
	return course_students;
}

size_t Curs::get_id()
{
	return id_course;
}

void Curs::add_professor(Profesor &p_tmp)
{
	course_professors.push_back(p_tmp);
}

/*------------------------End Class Curs---------------------------------*/

/*------------------------Class Absente---------------------------------*/

void Absente::add_absence()
{
	++total_absences;
}

void Absente::remove_absence()
{
	if (total_absences > 0) total_absences--;
}

void Absente::display_absence() const
{
	std::cout << "Data: " << absence_date << ", Motiv: " << absence_reason << "\n";
}

/*----------------------End Class Absente-----------------------------------*/
/*----------------------Class Catedra-----------------------------------------*/
void Catedra::add_students()
{
	system("cls");
	std::cin.ignore();
	size_t student_id = 1;
	std::string student_name = "default";

	std::cout << "Pentru sfarsit apasa enter" << std::endl;
	do
	{
		std::cout << "Introdu numele studentului: ";
		std::getline(std::cin, student_name);
		
		if (student_name.size() != 0)
		{
			Student student_temp(student_id, student_name);
			++student_id;
			students.push_back(student_temp);
		}
		else
			break;

	} while (true);
}

// Funcție pentru a adăuga un profesor
void Catedra::add_professor()
{
	system("cls");
	std::cin.ignore();
	size_t professor_id = 1;
	std::string professor_name;
	std::string professor_role;
	std::cout << "Pentru sfarsit apasa enter" << std::endl;

	do
	{
		std::cout << "Introdu numele profesorului: ";
		std::getline(std::cin, professor_name);
		if (professor_name.size() != 0)
		{
			std::cout << "Introdu rolul profesorului (titular, asistent etc.): ";
			std::getline(std::cin, professor_role);

			// Creăm un obiect Profesor cu datele introduse
			Profesor profesor(professor_id, professor_name, professor_role);
			professors.push_back(profesor);
			std::cout << "Profesorul a fost adaugat cu succes!" << std::endl;
			++professor_id;
		}
		else
			break;

	} while (true);
}

void Catedra::add_course()
{
	system("cls");
	std::cin.ignore();

	size_t course_id = 1;
	std::string course_name;

	std::cout << "Pentru sfarsit apasa enter" << std::endl;

	do
	{
		std::cout << "Introdu nume curs: ";
		std::getline(std::cin, course_name);
		if (course_name.size() != 0)
		{
			Curs curs_temp(course_id, course_name);
			courses.push_back(curs_temp);
			++course_id;
		}
		else
			break;

	} while (true);
	course_id = 1;
	for (const auto &x : courses)
	{
		course_prof_map[course_id] = x;
		++course_id;
	}
}

void Catedra::add_group()
{
	system("cls");
	std::cin.ignore();
	size_t group_id = 1;
	std::string group_name;
	int group_year = 0;

	std::cout << "Pentru sfarsit apasa enter" << std::endl;
	do
	{
		std::cout << "Introdu denumirea grupei: ";
		std::getline(std::cin, group_name);
		if (!group_name.empty())
		{
			std::cout << "Introdu anul grupei: ";
			std::cin >> group_year;
			std::cin.ignore();
			// Creăm obiectul de tip Grupa și îl adăugăm în map
			Grupa group_temp(group_id, group_name, group_year);

			groups.emplace(group_id, group_temp);
			++group_id;
			std::cout << "Grupa a fost adaugata cu succes!\n";
		}
		else
			break;

	} while (true);
}

void Catedra::add_students_to_group()
{
	system("cls");
	if (groups.empty())
	{
		std::cout << "Nu exista grupe!\n";
		return;
	}
	std::cin.ignore();
	for (const auto &group : groups)
	{
		std::cout << group.first << ": ";
		group.second.display_group();
		std::cout << std::endl;
	}

	size_t group_id;
	std::cout << "Introdu ID-ul grupei: ";
	std::cin >> group_id;
	std::cin.ignore();

	// Verificăm dacă grupa există
	if (groups.find(group_id) == groups.end()) {
		std::cout << "Grupa cu acest ID nu există!\n";
		return;
	}

	std::vector<Student> students_in_group;

	std::cout << "Pentru sfarsit apasa enter" << std::endl;
	size_t student_id = 1;
	std::string student_name;
	do
	{
		std::cout << "Introdu numele studentului: ";
		std::getline(std::cin, student_name);
		if (!student_name.empty())
		{
			students_in_group.emplace_back(student_id, student_name);
			++student_id;
		}
		else
			break;
	} while (true);

	groups[group_id].add_student(students_in_group);

	std::cout << "Studenți adăugați cu succes!\n";
}

void Catedra::add_professor_to_course()
{
	system("cls");
	for (const auto &course_entry : course_prof_map)
	{
		std::cout << course_entry.first << ": ";
		course_entry.second.display_course();
	}

	size_t course_id = 0;
	std::cout << "Alege cursul: ";
	std::cin >> course_id;
	std::cin.ignore();

	auto it_course = course_prof_map.find(course_id);
	/*auto it = std::find_if(curs.begin(), curs.end(), [&](Curs &p)
	{return p.get_id_curs() == id_curs; });*/

	if (it_course == course_prof_map.end())
	{
		std::cout << "Nu exista un curs cu acest ID!" << std::endl;
		return;
	}

	std::cout << "Cati profesori doresti sa adaugi la curs: ";
	int num_professors;
	std::cin >> num_professors;
	std::cin.ignore();
	std::cout << std::endl;
	if (professors.empty())
	{
		std::cout << "Nu sunt profesori adaugati!" << std::endl;
		return;
	}
	for (const auto &professor : professors)
		std::cout << professor.get_id() << ": " << professor.get_full_name() << std::endl;

	int i = 0;
	while (i < num_professors)
	{
		size_t professor_id = 0;
		std::cout << "Alege profesorul: ";
		std::cin >> professor_id;
		std::cin.ignore();
		std::cout << std::endl;

		auto it_professor = std::find_if(professors.begin(), professors.end(), [&](const Profesor &p)
		{return p.get_id() == professor_id; });

		if (it_professor != professors.end())
		{
			it_course->second.add_professor(*it_professor);
		}
		++i;
	}
}

void Catedra::add_students_to_course()
{
	system("cls");

	if (course_prof_map.empty()) {
		std::cout << "Nu sunt cursuri disponibile pentru adăugarea de studenți.\n";
		return;
	}

	// Afișează cursurile disponibile
	std::cout << "Cursurile disponibile:\n";
	for (const auto& curs_entry : course_prof_map) {
		std::cout << "ID Curs: " << curs_entry.first << "\n";
		curs_entry.second.display_course();  // Metoda pentru afișarea detaliilor cursului
	}

	size_t course_id = 0;
	std::cout << "Alege ID-ul cursului la care dorești să adaugi studenți: ";
	std::cin >> course_id;
	std::cin.ignore();

	// Caută cursul în mapa profesori_curs
	auto course_it = course_prof_map.find(course_id);
	if (course_it == course_prof_map.end()) {
		std::cout << "Nu există un curs cu acest ID.\n";
		return;
	}

	if (groups.empty()) {
		std::cout << "Nu sunt studenți disponibili în grupe.\n";
		return;
	}

	// Afișează studenții din fiecare grupă
	std::cout << "Studenții disponibili:\n";
	for (const auto& grupa_entry : groups) {
		std::cout << "Grupa " << grupa_entry.first << ":\n";
		grupa_entry.second.display_students_in_group();  // Metodă pentru afișarea studenților din grupă
	}

	size_t group_id = 0;
	std::cout << "Alege ID-ul grupei de unde dorești să adaugi studenți: ";
	std::cin >> group_id;
	std::cin.ignore();

	// Caută grupa în mapa grupe
	auto group_it = groups.find(group_id);
	if (group_it == groups.end()) {
		std::cout << "Nu s-a găsit grupa cu acest ID.\n";
		return;
	}

	// Obține studenții din grupă
	const Grupa& grupa = group_it->second;
	auto studenti = grupa.get_students();

	// Adaugă studenții la cursul selectat
	for (const auto &student : studenti) {
		course_it->second.add_single_student(student); // Metoda pentru a adăuga un student la curs
	}

	std::cout << "Studenți adăugați la cursul selectat.\n";
}

// Funcție pentru a afișa toate grupele
void Catedra::display_groups() const
{
	system("cls");
	if (groups.empty()) {
		std::cout << "Nu există grupe în sistem.\n";
	}
	else {
		std::cout << "Lista grupelor:\n";

		for (const auto& grupa_entry : groups) {
			const Grupa& group_obj = grupa_entry.second;

			// Afișează informațiile despre grupă
			group_obj.display_group();
			std::cout << std::endl;
		}
	}
}

// Funcție pentru a afișa toți studenții
void Catedra::display_students() const
{
	system("cls");
	if (groups.empty())
	{
		std::cout << "Nu sunt studenti.";
		return;
	}

	bool find_students = false;

	for (const auto &group_entry : groups)
	{
		const Grupa& group_obj = group_entry.second;
		// Verifică dacă grupa are studenți
		if (group_obj.get_num_students() > 0)
		{
			std::cout << "Grupa " << group_entry.first << ":\n";  // Afișează ID-ul grupei
			group_obj.display_group();
			group_obj.display_all_students();  // Afișează studenții din această grupă
			find_students = true;
		}
	}
	// Dacă nu a fost găsit niciun student în nicio grupă
	if (!find_students)
	{
		std::cout << "Nu sunt studenți în nicio grupă.\n";
	}
}

void Catedra::display_catedre() const
{
	std::cout << catedra_name;
}

// Funcție pentru a afișa toți profesorii
void Catedra::display_professors() const
{
	system("cls");
	if (professors.empty()) {
		std::cout << "Nu există profesori în sistem.\n";
	}
	else {
		std::cout << "Lista profesorilor:\n";
		for (const auto& profesor : professors) {
			std::cout << profesor.get_id() << ": " <<
				profesor.get_full_name() << " (" << profesor.get_role() << ")" << std::endl;
		}
	}
}

void Catedra::display_students_in_group() const
{
	system("cls");

	if (groups.empty()) {
		std::cout << "Nu sunt grupe disponibile.\n";
		return;
	}

	std::cout << "Alege grupa:" << std::endl;
	for (const auto &group_entry : groups)
	{
		std::cout << "ID Grupa: " << group_entry.first << std::endl; 
		group_entry.second.display_group();
		std::cout << std::endl;
	}
	short id_group = 0;
	std::cin >> id_group;

	// Verifică dacă grupa există
	auto group_it = groups.find(id_group);
	if (group_it == groups.end()) {
		std::cout << "Nu există o grupă cu acest ID.\n";
		return;
	}
	if (group_it->second.get_num_students() == 0)
	{
		std::cout << "Nu există studenti in aceasta grupa." << std::endl;
		return;
	}
	// Afișează studenții din grupa selectată
	const Grupa& group_obj = group_it->second;
	std::cout << "Studenții din grupa " << id_group << ":\n";
	group_obj.display_students_in_group();
}

void Catedra::display_students_in_course() const
{
	system("cls");
	for (const auto &course_entry : course_prof_map)
	{
		course_entry.second.display_course();
	}
	std::cout << "Alege cursul:\n";
	short id_course;
	std::cin >> id_course;
	std::cin.ignore();

	auto course_it = course_prof_map.find(id_course);
	if (course_it == course_prof_map.end())
	{
		std::cout << "Nu este asa curs" << std::endl;
		return;
	}

	course_it->second.display_students_in_course();
}

void Catedra::display_professors_in_course() const
{
	system("cls");
	std::cout << "Alege cursul:\n";
	short id_course;
	std::cin >> id_course;
	std::cin.ignore();

	auto it_professor = course_prof_map.find(id_course);
	if (it_professor == course_prof_map.end())
	{
		std::cout << "Nu este asa curs" << std::endl;
		return;
	}
	it_professor->second.display_professors_in_course();
}

/*----------------------End Class Catedra-----------------------------------------*/

/*----------------------Class SystemManagement-----------------------------------*/

void SystemManagement::add_catedra()
{
	system("cls");
	std::cin.ignore();
	std::cout << "Pentru sfarsit apasa enter" << std::endl;
	short i = 1;

	do
	{
		std::cout << "Introdu nume catedra: ";
		std::string nume_catedra;
		std::getline(std::cin, nume_catedra);
		if (!nume_catedra.empty())
		{
			catedre[i] = Catedra(nume_catedra);
			++i;
		}
		else
			break;

	} while (true);

}

void SystemManagement::remove_catedra()
{
	system("cls");
	for (const auto catedra_entry : catedre)
	{
		std::cout << catedra_entry.first << ": ";
		catedra_entry.second.display_catedre();
		std::cout << std::endl;
	}
	std::cout << "introdu id catedra: ";
	int id_catedra;
	std::cin >> id_catedra;
	std::cin.ignore();
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
void SystemManagement::display_catedre() const
{
	system("cls");
	for (const auto catedra_entry : catedre)
	{
		std::cout << catedra_entry.first << ": ";
		catedra_entry.second.display_catedre();
		std::cout << std::endl;
	}
}
//
//// Implementare actualizare informatii catedra
//void SystemManagement::update_info_catedra() {
//	size_t id;
//	std::cout << "Introdu ID-ul catedrei pe care vrei sa o actualizezi: ";
//	std::cin >> id;
//
//	auto it = catedre.find(id);
//	if (it == catedre.end()) {
//		std::cout << "Catedra nu exista!\n";
//		return;
//	}
//
//	std::string new_name;
//	std::cout << "Introdu noul nume pentru catedra: ";
//	std::cin.ignore();
//	std::getline(std::cin, new_name);
//
////	it->second.set_name(new_name); 
//	std::cout << "Informatiile catedrei au fost actualizate cu succes.\n";
//}
//
void SystemManagement::add_group_to_catedra() {
	size_t id_catedra;
	std::cout << "Introdu ID-ul catedrei: ";
	std::cin >> id_catedra;

	auto it = catedre.find(id_catedra); // Caută catedra
	if (it == catedre.end()) {
		std::cout << "Catedra cu ID-ul " << id_catedra << " nu a fost găsită.\n";
		return;
	}
	it->second.add_group();

}

void SystemManagement::add_students_to_catedra()
{
	system("cls");
	std::cout << "Introdu id-ul catedra: ";
	size_t catedra_id;
	std::cin >> catedra_id;

	auto it_catedra = catedre.find(catedra_id);
	if (it_catedra != catedre.end())
	{
		it_catedra->second.add_students();
		std::cout << "Studenti adaugati cu succes" << std::endl;
	
	}
	
}

void SystemManagement::add_professor_to_catedra()
{
	system("cls");
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
	system("cls");
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
	std::cout << "Introdu id-ul catedra: ";
	size_t catedra_id;
	std::cin >> catedra_id;

	auto it_catedra = catedre.find(catedra_id);

	if (it_catedra != catedre.end())
	{
		it_catedra->second.add_students_to_course();
		std::cout << "Profesori adaugati cu succes" << std::endl;
	}
}

void SystemManagement::add_professor_to_course()
{
	system("cls");
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

/*------------------------End Class SystemManagement---------------------------------*/