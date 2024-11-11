#include "IncludesCentral.h"

void Curs::insert_into_db() const {
	std::string query = "INSERT INTO courses (id, course_name) VALUES (" +
		std::to_string(id_course) + ", '" + course_name + "')";
	db_conn.executeQuery(query);
}

void Curs::add_students(const std::vector<Student> &student_list)
{
	course_students.insert(course_students.end(), student_list.begin(), student_list.end());
}

void Curs::add_single_student(const Student &new_student)
{
	course_students.push_back(new_student);
}

void Curs::add_grade_for_student(std::string name_course, Student &student, double grade) {
	nota.add_grade(name_course, student, grade); // Deleagă adăugarea notei către clasa Nota
}

void Curs::add_professor(Profesor &p_tmp)
{
	course_professors.push_back(p_tmp);
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

void Curs::display_students_absences() const
{
	absente.display_absence();
}

void Curs::display_course() const
{
	std::cout << " Curs: " << course_name << "\n";
}

void Curs::display_students_grades() const
{
	nota.display_grades();
}

//std::vector<Student> Curs::get_students() const
//{
//	return course_students;
//}

size_t Curs::get_id()
{
	return id_course;
}

void Curs::add_absence_for_student(std::string &name_course, const Student &student, std::string &absence)
{
	absente.add_absence(name_course, student, absence);
}
