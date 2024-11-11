#include "IncludesCentral.h"


void Nota::add_grade(std::string name_course, Student &student, double grade)
{
	auto now = std::chrono::system_clock::now();  // Obține timpul curent
	this->course_name = name_course;
	grades[student].emplace_back(grade, now);      // Adaugă nota cu data
}

double Nota::calculate_average(const Student& student) const
{
	auto it = grades.find(student);
	if (it != grades.end() && !it->second.empty()) {
		double sum = 0;
		for (const auto& nota : it->second) {
			sum += nota.get_value();
		}
		return sum / it->second.size();
	}
	return 0.0;  // Returnează 0 dacă studentul nu are note
}

bool Nota::search_grade(const Student& student, double grade_to_search) const
{
	auto it = grades.find(student);
	if (it != grades.end()) {
		for (const auto& nota : it->second) {
			if (nota.get_value() == grade_to_search) {
				return true;  // Nota a fost găsită
			}
		}
	}
	return false; // Nota nu a fost găsită
}

void Nota::display_grades() const
{
	for (const auto& pair : grades) {
		const Student& student = pair.first;
		const std::vector<NotaDetaliata> &student_grades = pair.second;

		std::cout << "Curs: " << course_name << std::endl;
		std::cout << "Student: " << student.get_name() << " - Note: ";
		for (const auto& nota : student_grades)
		{
			std::cout << ": " << nota.get_value() << " (Date: " << nota.get_date() << ") ";
		}
		std::cout << std::endl;
	}
}

