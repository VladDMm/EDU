#pragma once
#ifndef ABSENTE
#define ABSENTE

class AbsentaDetaliata {
public:

	AbsentaDetaliata(std::string reason, const std::chrono::system_clock::time_point &date)
		: reason(reason), date(date)
	{
		++total_absences;
	}

	std::string get_reason() const { return reason; }

	short get_total_absence() const { return total_absences; }

	std::string get_date() const
	{
		std::time_t tt = std::chrono::system_clock::to_time_t(date);
		std::stringstream ss;
		ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
		return ss.str();
	}

private:
	size_t total_absences = 0;
	std::string reason;
	std::chrono::system_clock::time_point date; // Data și ora adăugării notei
};

class Absente {
public:
	Absente() {}

	Absente(const std::string &course_name) : course_name(course_name) {}

	void add_absence(std::string &, const Student &, std::string &);

	void remove_absence(const Student &);

	void display_absence() const;

private:
	std::string course_name;  // Numele cursului pentru care se țin notele
	std::map<Student, std::vector<AbsentaDetaliata>> absences;  // Map între student și notele sale detaliate

};



#endif // !ABSENTE
