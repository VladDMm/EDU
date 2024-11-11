#pragma once
#ifndef DATABASECONNECT
#define DATABASECONNECT

class DatabaseConnection
{
public:
	DatabaseConnection();

	~DatabaseConnection()
	{
		if (conn) {
			conn->close();
		}
	}

	// Metodă pentru a executa un query
	void executeQuery(const std::string &query);

	std::vector<std::tuple<int, std::string, std::string, std::string, int>> selectStudents();

	// Metodă pentru a executa un query de tip SELECT student
	//std::vector<std::pair<int, std::string>> selectStudents(const std::string& query);

	// Metodă pentru a executa un query de tip SELECT departments
	std::vector<std::pair<int, std::string>> selectDepartments(const std::string& query);

	void displayGroups_from_bd()const;

	// Metodă pentru a actualiza catedra
	void updateCatedra(int id, const std::string &newName);

	void addGroupToDatabase(const std::string& groupName, int groupYear, int id_catedra);

	// Metodă pentru a obține ultimul ID inserat
	int getLastInsertId();
	int getLastInsertId(const char *query);

private:
	sql::Driver *driver;
	std::unique_ptr<sql::Connection> conn;
};


#endif