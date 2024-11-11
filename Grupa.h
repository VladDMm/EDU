#pragma once
#ifndef GRUPA
#define GRUPA


class Grupa
{
public:
	Grupa() {}

	// Constructor to initialize group with ID, name, and year
	Grupa(size_t id, const std::string& name, int year) :
		id_group(id), group_name(name), year_of_study(year) {}
	// Constructor to initialize group with students
	//Grupa(std::vector<Student> &student_vector)
	//{ students.insert(students.begin(), student_vector.begin(), student_vector.end()); }

	// Add students to the group
	void add_student(std::vector<Student> &);
	void add_student(std::map<size_t, Student>::iterator &);

	// Display students in the group
	void display_students_in_group() const;
	void display_all_students() const;

	// Remove a student by ID
	void remove_student(size_t);

	// Display group details
	void display_group() const;

	// Get the group ID
	size_t get_id() const;

	// Get a list of students in the group
	const std::vector<Student> get_students() const;

	// Get the number of students
	size_t get_num_students() const;

private:
	size_t id_group;
	std::string group_name;
	int year_of_study;
	std::vector<Student> students;
};

#endif // ! GRUPA
