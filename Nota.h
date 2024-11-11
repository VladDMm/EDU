#pragma once
#ifndef NOTE
#define NOTE
class NotaDetaliata {
public:

	NotaDetaliata(double value, const std::chrono::system_clock::time_point &date)
		: value(value), date(date) {}

	double get_value() const { return value; }

	std::string get_date() const
	{
		std::time_t tt = std::chrono::system_clock::to_time_t(date);
		std::stringstream ss;
		ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
		return ss.str();
	}

private:
	double value;
	std::chrono::system_clock::time_point date; // Data și ora adăugării notei
};

class Nota {
public:
	Nota() {}

	Nota(const std::string& course) : course_name(course) {}

	// Adaugă o notă pentru un student
	void add_grade(std::string, Student& student, double);

	// Calculează media notelor pentru un student
	double calculate_average(const Student& student) const;

	// Caută o notă specifică pentru un student
	bool search_grade(const Student&, double) const;

	// Afișează toate notele pentru toți studenții
	void display_grades() const;

private:
	std::string course_name;  // Numele cursului pentru care se țin notele
	std::map<Student, std::vector<NotaDetaliata>> grades;  // Map între student și notele sale detaliate
};


#endif