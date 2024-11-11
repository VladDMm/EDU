#pragma once
#ifndef ADMINISTRATOR
#define ADMINISTRATOR


class Administrator : public User
{
public:
	Administrator() {}

	Administrator(SystemManagement *sistem) : sistem(SystemManagement::getInstance()) {}

	Administrator(size_t id_user, std::string &name, const std::string &email, std::string &user, std::string &pass, SystemManagement *sistem) : User(id_user, name, email, user, pass, UserType::admin), sistem(SystemManagement::getInstance()) {}

	void show_menu() override;

	// Funcție pentru crearea obiectului de tip User în funcție de rol
	//std::unique_ptr<User> create_user(const std::string& user, const std::string& pass, const std::string& name, User::UserType type) {
	//	switch (type) {
	//	case User::UserType::student:
	//		return std::make_unique<Student>(user, pass, name);
	//	case User::UserType::profesor:
	//		return std::make_unique<Profesor>(user, pass, name);
	//	case User::UserType::admin:
	//		return std::make_unique<Administrator>(user, pass, name);
	//	default:
	//		return nullptr;
	//	}
	//}

	//Administrator* authenticate_admin(std::string &user, std::string &pass);

	~Administrator() override = default;

private:
	SystemManagement *sistem;
};

#endif // !1

