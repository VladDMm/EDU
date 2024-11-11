#pragma once
#ifndef PROFESSORS
#define PROFESSORS


class Profesor : public User
{
public:
	Profesor() {}

	Profesor(size_t id, const std::string &name, std::string &role)
		: id_professor(id), full_name(name), professor_role(role) {}

	Profesor(size_t id, const std::string &name, const std::string &email, std::string &role, std::string &user, std::string &pass)
		: id_professor(id), full_name(name), professor_role(role), User(id, name, email, user, pass, UserType::profesor) {}

	Profesor(const std::string &name, const std::string &email, std::string &role, std::string &user, std::string &pass)
		: full_name(name), professor_role(role), User(name, email, user, pass, UserType::profesor) {}

	void show_menu() override;

	size_t get_id_prof() const;

	std::string get_full_name() const;

	std::string get_role() const;

	~Profesor() override = default;

	void insert_into_db() const;


private:
	size_t id_professor = 0;
	unsigned short catedra_id = 0;
	std::string full_name;
	std::string professor_role;
};

#endif // !PROFESSORS