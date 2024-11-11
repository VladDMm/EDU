#include "IncludesCentral.h"

void Absente::add_absence(std::string &name_course, const Student &student, std::string &reason)
{
	auto now = std::chrono::system_clock::now();  // Obține timpul curent
	this->course_name = name_course;
	absences[student].emplace_back(reason, now);      // Adaugă absenta cu data
}

void Absente::display_absence() const
{
	for (const auto& pair : absences) {
		const Student& student = pair.first;
		const std::vector<AbsentaDetaliata> &student_absences = pair.second;

		std::cout << "Curs: " << course_name << std::endl;
		std::cout << "Student: " << student.get_name() << " - Absente: ";
		for (const auto& nota : student_absences)
		{
			std::cout << ": " << nota.get_reason() << " (Date: " << nota.get_date() << ") ";
		}
		std::cout << std::endl;
	}
}

void Absente::remove_absence(const Student &student)
{

}