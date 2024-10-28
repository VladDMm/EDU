#include <algorithm>
#include "academic_records.h"

/*------------------------Class Administrator---------------------------------*/

void Administrator::show_menu()
{
	short option;
	do
	{
		std::cout << "1. Adauga catedra" << std::endl;
		std::cout << "2. Adauga grupa la catedra" << std::endl;
		std::cout << "3. Adauga studenti la catedra" << std::endl;
		std::cout << "4. Adauga profesori la catedra" << std::endl;
		std::cout << "5. Adauga curs la catedra" << std::endl;
		std::cout << "6. Adauga studenti la grupa" << std::endl;
		std::cout << "7. Adauga studenti la curs" << std::endl;
		std::cout << "8. Adauga profesori la curs" << std::endl;
		std::cout << "9. Afiseaza catedre" << std::endl;
		std::cout << "10. Sterge catedra" << std::endl;
		std::cout << "0. Iesi" << std::endl;
		std::cout << "Alege optiunea: " << std::endl;
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

	} while (option != 0);

}

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
	std::cout  << "Nume: " << full_name;
}

size_t Student::get_id() const
{
	return id_student;
}

std::string Student::get_name() const 
{
	return full_name;
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
			if (catedra)
			{
				std::cout << "Afisare cursuri inscrise pentru catedra: " << catedra->get_name_catedra() << "\n";
				catedra->show_student_courses(id_student);
			}

			std::cout << "Nu esti înscris la nicio catedră.\n";
			break;
		}
		case 2:
		{
			
			break;
		}
		case 0:
			break;
		default:
			break;
		}

	} while (option != 0);

}

/*----------------------End Class Student-----------------------------------*/

/*----------------------Class Profesor-----------------------------------*/

void Profesor::show_menu()
{
	SystemManagement *system = SystemManagement::getInstance();

	// Apelează get_catedra_profesor pentru a obtine catedra profesorului curent
	const Catedra* catedra = system->get_catedra_profesor(id_professor);

	if (!catedra)
	{
		std::cout << "Nu esti inscris la nici o catedra" << std::endl;
		return;
	}

	std::cout << "1. Afisare cursuri disponibile" << std::endl;
	std::cout << "2. Afisare studenti la curs" << std::endl;
	std::cout << "3. Adauga nota si absenta la curs" << std::endl;
	std::cout << "4. Actualizeaza nota si absenta la curs" << std::endl;
	std::cout << "0. Iesi" << std::endl;

	short option;
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

		break;
	}
	case 4:
	{
		break;
	}
	case 0:
		break;
	default:
		std::cout << "Alegere incorecta!" << std::endl;
		break;
	}
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

/*------------------------End Class Profesor---------------------------------*/

/*----------------------Class Grupa-----------------------------------*/

void Grupa::add_student(std::vector<Student> &student_vector)
{
	students.insert(students.begin(), student_vector.begin(), student_vector.end());
}

void Grupa::add_student(std::map<size_t, Student>::iterator &it)
{
	
	students.push_back(it->second);
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


//double Nota::calculate_average() const
//{
//	if (grades.empty()) return 0.0;
//	double suma = 0;
//	for (double n : grades) {
//		suma += n;
//	}
//	return suma / grades.size();
//}

void Nota::search_grade(double grade_to_search) const
{
	
}

void Nota::display_grades() const
{
	std::cout << "Note: ";
	for (const auto &pair : grades) 
	{
		std::cout << course_name << std::endl;
		std::cout << pair.first.get_name() << ": ";
		for (const auto &it : pair.second)
			std::cout << it.first << "  " << it.second << std::endl;
	}
}

/*-------------------------End Class Nota--------------------------------*/

/*-------------------------Class Curs--------------------------------*/

//Curs Curs::get_course() const
//{
//	return Curs(id_course, course_name);
//}

void Curs::add_students(const std::vector<Student> &student_list)
{
	course_students.insert(course_students.end(), student_list.begin(), student_list.end());
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

std::vector<size_t> Curs::get_id_students() const
{
	std::vector<size_t> ids;
	for (const auto &student : course_students)
		ids.push_back(student.get_id());
	return ids;
}

std::vector<size_t> Curs::get_id_professors() const
{
	std::vector<size_t> ids;
	for (const auto &prof : course_professors)
		ids.push_back(prof.get_id_prof());
	return ids;
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
	for (const auto &profesor : course_professors)
		std::cout << profesor.get_id_prof() << ": " << profesor.get_full_name()
		<< " (" << profesor.get_role() << ")" << std::endl;
}

void Curs::display_course() const
{
	std::cout <<" Curs: " << course_name << "\n";
}

//std::vector<Student> Curs::get_students() const
//{
//	return course_students;
//}

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
	std::string student_name;
	if (!students.empty())
	{
		student_id = (--students.end())->first;
		++student_id;
		std::cout << "Pentru sfarsit apasa enter" << std::endl;
		do
		{
			std::cout << "Introdu numele studentului: ";
			std::getline(std::cin, student_name);

			if (student_name.size() != 0)
			{
				std::string user, pass;
				std::cout << "Introdu username-ul: ";
				std::cin >> user;
				std::cout << "Introdu parola: ";
				std::cin >> pass;

				Student student_temp(student_id, student_name, user, pass);
				students[student_id] = student_temp;
				++student_id;
				std::cin.ignore();
			}
			else
				break;

		} while (true);
	}

	else
	{
		std::cout << "Pentru sfarsit apasa enter" << std::endl;
		do
		{
			std::cout << "Introdu numele studentului: ";
			std::getline(std::cin, student_name);

			if (student_name.size() != 0)
			{
				std::string user, pass;
				std::cout << "Introdu username-ul: ";
				std::cin >> user;
				std::cout << "Introdu parola: ";
				std::cin >> pass;

				Student student_temp(student_id, student_name, user, pass);
				students[student_id] = student_temp;
				//	students.emplace_back(student_id, student_name);
				++student_id;
				std::cin.ignore();
				//students.push_back(student_temp);
			}
			else
				break;

		} while (true);
	}
	
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

	if (!professors.empty())
	{
		professor_id = (--professors.end())->first;
		++professor_id;
		do
		{
			std::cout << "Introdu numele profesorului: ";
			std::getline(std::cin, professor_name);
			if (professor_name.size() != 0)
			{
				std::cout << "Introdu rolul profesorului (titular, asistent etc.): ";
				std::getline(std::cin, professor_role);
				std::cout << "Introdu username: ";
				std::string user, pass;
				std::cin >> user;
				std::cout << "Introdu parola: ";
				std::cin >> pass;
				std::cin.ignore();
				// Creăm un obiect Profesor cu datele introduse
				Profesor profesor_temp(professor_id, professor_name, professor_role, user, pass);
				professors[professor_id] = profesor_temp;
				std::cout << "Profesorul a fost adaugat cu succes!" << std::endl;
				++professor_id;
			}
			else
				break;

		} while (true);
	}

	else
	{
		do
		{
			std::cout << "Introdu numele profesorului: ";
			std::getline(std::cin, professor_name);
			if (professor_name.size() != 0)
			{
				std::cout << "Introdu rolul profesorului (titular, asistent etc.): ";
				std::getline(std::cin, professor_role);
				std::cout << "Introdu username: ";
				std::string user, pass;
				std::cin >> user;
				std::cout << "Introdu parola: ";
				std::cin >> pass;
				std::cin.ignore();
				// Creăm un obiect Profesor cu datele introduse
				Profesor profesor_temp(professor_id, professor_name, professor_role, user, pass);
				professors[professor_id] = profesor_temp;
				std::cout << "Profesorul a fost adaugat cu succes!" << std::endl;
				++professor_id;
			}
			else
				break;

		} while (true);
	}
}

void Catedra::add_course()
{
	system("cls");
	std::cin.ignore();

	size_t course_id = 1;
	std::string course_name;

	if (!course_prof_map.empty())
	{
		course_id = (--course_prof_map.end())->first;
		++course_id;

		std::cout << "Pentru sfarsit apasa enter" << std::endl;

		do
		{
			std::cout << "Introdu nume curs: ";
			std::getline(std::cin, course_name);
			if (course_name.size() != 0)
			{
				Curs curs_temp(course_id, course_name);
				course_prof_map[course_id] = curs_temp;
				++course_id;
			}
			else
				break;

		} while (true);

	/*	course_id = (--course_prof_map.end())->first;
		++course_id;
		for (const auto &x : courses)
		{
			course_prof_map[course_id] = x;
			++course_id;
		}*/
	}

	else
	{
		std::cout << "Pentru sfarsit apasa enter" << std::endl;
		do
		{
			std::cout << "Introdu nume curs: ";
			std::getline(std::cin, course_name);
			if (course_name.size() != 0)
			{
				Curs curs_temp(course_id, course_name);
				course_prof_map[course_id] = curs_temp;
				//courses.push_back(curs_temp);
				++course_id;
			}
			else
				break;

		} while (true);
	}
	
}

void Catedra::add_group()
{
	system("cls");
	std::cin.ignore();

	if (!groups.empty())
	{
		size_t group_id = (--groups.end())->first;
		++group_id;
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
	else
	{
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
	
}

void Catedra::add_students_to_group()
{
	system("cls");
	std::cin.ignore();
	if (students.empty())
	{
		std::cout << "Nu exista studenti!\n";
		return;
	}

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

	for (auto &x : students)
	{
		std::cout << x.first << ": ";
		x.second.display_student();
		std::cout << std::endl;
	}
	size_t id;
	do
	{
		std::cout << "Alege id-ul studentilor(pentru iesire apasa 0):" << std::endl;
		std::cin >> id;
		if (id == 0)
			break;
		auto it = students.find(id);
		groups[group_id].add_student(it);

	} while (true);
	

	//std::vector<Student> students_in_group;
	//std::cout << "Pentru sfarsit apasa enter" << std::endl;
	//size_t student_id = 1;
	//std::string student_name;
	//do
	//{
	//	std::cout << "Introdu numele studentului: ";
	//	std::getline(std::cin, student_name);
	//	if (!student_name.empty())
	//	{
	//		students_in_group.emplace_back(student_id, student_name);
	//		++student_id;
	//	}
	//	else
	//		break;
	//} while (true);
	//groups[group_id].add_student(students_in_group);
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
		std::cout << professor.second.get_id_prof() << ": " << professor.second.get_full_name() << std::endl;

	int i = 0;
	while (i < num_professors)
	{
		size_t professor_id = 0;
		std::cout << "Alege profesorul: ";
		std::cin >> professor_id;
		std::cin.ignore();
		std::cout << std::endl;
		auto it_professor = professors.find(professor_id);
		//auto it_professor = std::find_if(professors.begin(), professors.end(), [&](const Profesor &p)
		//{return p.get_id() == professor_id; });

		if (it_professor != professors.end())
		{
			it_course->second.add_professor(it_professor->second);
		}
		++i;
	}
	std::cout << "Profesori adaugati cu succes!";
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
		curs_entry.second.display_course();  // Metoda pentru afiaarea detaliilor cursului
	}

	size_t course_id = 0;
	std::cout << "Alege ID-ul cursului la care dorești să adaugi studenți: ";
	std::cin >> course_id;
	std::cin.ignore();

	// Caută cursul în mapa profesori_curs
	auto course_it = course_prof_map.find(course_id);
	if (course_it == course_prof_map.end()) 
	{
		std::cout << "Nu există un curs cu acest ID.\n";
		return;
	}

	if (groups.empty())
	{
		std::cout << "Nu sunt studenți disponibili în grupe.\n";
		return;
	}

	// Afișează studenții din fiecare grupă
	std::cout << "Studenții disponibili:\n";
	for (const auto& grupa_entry : groups) 
	{
		std::cout << "Grupa " << grupa_entry.first << ":\n";
		grupa_entry.second.display_students_in_group();  // Metodă pentru afișarea studenților din grupă
	}

	size_t group_id = 0;
	std::cout << "Alege ID-ul grupei de unde dorești să adaugi studenți: ";
	std::cin >> group_id;
	std::cin.ignore();

	// Cauta grupa in mapa grupe
	auto group_it = groups.find(group_id);
	if (group_it == groups.end()) 
	{
		std::cout << "Nu s-a găsit grupa cu acest ID.\n";
		return;
	}
	
	const Grupa& grupa = group_it->second;
	// Obține studentii din grupa
	auto studenti = grupa.get_students();
	course_it->second.add_students(studenti);

	// Adauga studentii la cursul selectat
	//for (const auto &student : studenti)
	//{
	//	course_it->second.add_single_student(student); // Metoda pentru a adauga un student la curs
	//}

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

void Catedra::show_professor_courses(size_t id_profesor) const
{
	for (const auto &x : course_prof_map)
	{
		// Obține lista de ID-uri ale profesorilor din curs
		std::vector<size_t> professor_ids = x.second.get_id_professors();
		
		// Verifică dacă ID-ul profesorului se află în lista de ID-uri
		if (std::find(professor_ids.begin(), professor_ids.end(), id_profesor) != professor_ids.end())
		{
			std::cout << x.first << ": ";
			// Afișează detalii despre curs dacă profesorul este înscris la acest curs
			x.second.display_course();
		}
	}
}
// Afiseaza cursurile pentru studentul specific, functie pentru studenti
void Catedra::show_student_courses(size_t id_student) const
{
	for (const auto &x : course_prof_map)
	{
		// Obține lista de ID-uri ale studenților din curs
		std::vector<size_t> student_ids = x.second.get_id_students();

		// Verifică dacă ID-ul studentului se află în lista de ID-uri
		if (std::find(student_ids.begin(), student_ids.end(), id_student) != student_ids.end())
		{
			// Afișează detalii despre curs dacă studentul este înscris la acest curs
			x.second.display_course();
		}
	}
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
			std::cout << profesor.second.get_id_prof() << ": " <<
				profesor.second.get_full_name() << " (" << profesor.second.get_role() << ")" << std::endl;
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
	//const Grupa& group_obj = group_it->second;
	std::cout << "Studenții din grupa " << id_group << ":\n";
	group_it->second.display_students_in_group();
}
// Afisare studentii de la curs dupa cursurile care ii apartin profesorului
void Catedra::display_students_in_course_by_prof(size_t id_prof) const
{
	system("cls");
	this->show_professor_courses(id_prof);

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


	//short option;
	//do
	//{
	//	std::cout << "1. Afisare studenti la curs" << std::endl;
	//	std::cout << "2. Adauga nota la curs" << std::endl;
	//	std::cout << "3. Adauga absenta la curs" << std::endl;
	//	std::cout << "0. Iesi" << std::endl;
	//	std::cin >> option;
	//	switch (option)
	//	{
	//	case 1:
	//	{
	//		short id;
	//		std::cin >> id;
	//		auto it_course = course_prof_map.find(id);
	//		if (it_course == course_prof_map.end())
	//		{
	//			std::cout << "Id incorect" << std::endl;
	//			return;
	//		}
	//		it_course->second.display_students_in_course();
	//		break;
	//	}
	//	case 2:
	//	{
	//		break;
	//	}
	//	case 3:
	//	{
	//		break;
	//	}
	//	case 0:
	//		break;
	//	default:
	//		std::cout << "Alegere incorecta" << std::endl;
	//		break;
	//	}
	//} while (option != 0);	
}
// Afisarea studentilor dupa cursurile selectate, functie pentru admin
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
// Afisarea profesorilor dupa cursurile selectate, functie pentru admin
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

// Verifică dacă un student este în această catedră
bool Catedra::has_student(size_t id_student) const {
	return students.find(id_student) != students.end();
}
// Verifica daca un profesor este in aceasta catedra
bool Catedra::has_professor(size_t id_profesor) const
{
	return professors.find(id_profesor) != professors.end();
}

Student* Catedra::authenticate_student(std::string &usern, std::string &pass)
{
	for (auto &pair : students)
	{
		if (pair.second.get_username() == usern && pair.second.get_passw() == pass)
			return &(pair.second);
	}
	return nullptr; // daca nu se găseste studentul
}

/*----------------------End Class Catedra-----------------------------------------*/

/*----------------------Class SystemManagement-----------------------------------*/

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
				catedre[id] = Catedra(id, nume_catedra);
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
				catedre[id] = Catedra(id, nume_catedra);
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
	for (const auto catedra_entry : catedre)
	{
		std::cout << catedra_entry.first << ": " 
			<< catedra_entry.second.get_name_catedra() << std::endl;
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
		std::cout << catedra_entry.first << ": " 
			<< catedra_entry.second.get_name_catedra() << std::endl;
	}
}
// Implementare actualizare informatii catedra
void SystemManagement::update_info_catedra() {
	size_t id;
	std::cout << "Introdu ID-ul catedrei pe care vrei sa o actualizezi: ";
	std::cin >> id;

	auto it = catedre.find(id);
	if (it == catedre.end()) {
		std::cout << "Catedra nu exista!\n";
		return;
	}

	std::string new_name;
	std::cout << "Introdu noul nume pentru catedra: ";
	std::cin.ignore();
	std::getline(std::cin, new_name);

//	it->second.set_name(new_name); 
	std::cout << "Informatiile catedrei au fost actualizate cu succes.\n";
}

void SystemManagement::add_group_to_catedra()
{
	for (const auto &x : catedre)
		std::cout << x.first << ": " <<
		x.second.get_name_catedra() << std::endl;

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

	for (const auto &x : catedre)
		std::cout << x.first << ": " <<
		x.second.get_name_catedra() << std::endl;

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

const Catedra* SystemManagement::get_catedra_profesor(size_t id_profesor) 
{
	for (const auto& catedra_pair : catedre)
	{
		const Catedra& catedra = catedra_pair.second;
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

/*------------------------End Class SystemManagement---------------------------------*/