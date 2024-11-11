#include "IncludesCentral.h"

DatabaseConnection db_conn;

DatabaseConnection::DatabaseConnection()
{
	// Configurare conexiune
	//sql::SQLString url("jdbc:mariadb://localhost:3306/academic_records");
	sql::SQLString url("jdbc:mariadb://localhost:3306/EDU");
	sql::Properties properties({ {"user", "root"}, {"password", "root"} });
	// Conectează la baza de date
	try {
		driver = sql::mariadb::get_driver_instance();  // Obține driverul MariaDB
		conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
		//std::cout << "Conexiune reușită!" << std::endl;
	}
	catch (sql::SQLException &e) {
		std::cerr << "Eroare de conexiune: " << e.what() << std::endl;
	}
}

int DatabaseConnection::getLastInsertId()
{
	try
	{
		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT LAST_INSERT_ID()"));

		if (res->next())
		{
			return res->getInt(1);
		}
		else
		{
			std::cerr << "Nu s-a putut obține ultimul ID inserat." << std::endl;
			return -1;
		}
	}
	catch (sql::SQLException &e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
		return -1;
	}
}

int DatabaseConnection::getLastInsertId(const char *query)
{
	try
	{
		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

		if (res->next())
		{
			return res->getInt(1);
		}
		else
		{
			std::cerr << "Nu s-a putut obține ultimul ID inserat." << std::endl;
			return -1;
		}
	}
	catch (sql::SQLException &e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
		return -1;
	}
}

void DatabaseConnection::addGroupToDatabase(const std::string& groupName, int groupYear, int id_catedra)
{
	try
	{
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO groups (group_name, study_year, department_id) VALUES (?, ?, ?)"));
		pstmt->setString(1, groupName);
		pstmt->setInt(2, groupYear);
		pstmt->setInt(3, id_catedra);
		pstmt->executeUpdate();
		std::cout << "Grupa a fost adaugata cu succes in baza de date!" << std::endl;
	}
	catch (sql::SQLException &e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
	}
}

void DatabaseConnection::updateCatedra(int id, const std::string &newName)
{
	try
	{
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("UPDATE departments SET department_name = ? WHERE department_id = ?"));
		pstmt->setString(1, newName);

		pstmt->setInt(2, id);
		int affectedRows = pstmt->executeUpdate();

		if (affectedRows > 0)
		{
			std::cout << "Catedra cu ID-ul " << id << " a fost actualizată cu succes." << std::endl;
		}
		else
		{
			std::cout << "Nu s-a găsit o catedră cu acest ID." << std::endl;
		}
	}
	catch (sql::SQLException &e)
	{
		std::cerr << "SQL Exception: " << e.what() << std::endl;
	}
}

void DatabaseConnection::displayGroups_from_bd()const
{
	const std::string query = "Select group_id, group_name, study_year FROM groups";
	try {
		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

		while (res->next())
		{
			int id = res->getInt("group_id");
			sql::SQLString name = res->getString("group_name");
			int year_study = res->getInt("study_year");
			std::cout << id << ": " << name << ", An studii: " << year_study << std::endl;
		}
	}
	catch (sql::SQLException& e) {
		std::cerr << "Query failed: " << query << "\nError: " << e.what() << std::endl;
	}
}

std::vector<std::pair<int, std::string>> DatabaseConnection::selectDepartments(const std::string& query) {
	std::vector<std::pair<int, std::string>> results;
	try {
		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

		while (res->next())
		{
			int id = res->getInt("department_id");
			sql::SQLString name = res->getString("department_name");
			results.emplace_back(id, name);
		}
	}
	catch (sql::SQLException& e) {
		std::cerr << "Query failed: " << query << "\nError: " << e.what() << std::endl;
	}
	return results;
}

// Metodă pentru a obține lista de studenți
std::vector<std::tuple<int, std::string, std::string, std::string, int>> DatabaseConnection::selectStudents() {
	std::vector<std::tuple<int, std::string, std::string, std::string, int>> students;
	try {
		std::string query =
			"SELECT s.student_id, u.fullname, u.email, u.username, s.group_id "
			"FROM students s "
			"JOIN users u ON s.user_id = u.user_id";
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		while (res->next()) {
			int student_id = res->getInt("student_id");
			sql::SQLString fullname = res->getString("fullname");
			sql::SQLString email = res->getString("email");
			sql::SQLString username = res->getString("username");
			int group_id = res->getInt("group_id");
			/*std::string fullname = res->getString("fullname");
			std::string email = res->getString("email");
			std::string username = res->getString("username");*/

			students.emplace_back(student_id, fullname, email, username, group_id);
		}
	}
	catch (sql::SQLException &e) {
		std::cerr << "SQL Exception: " << e.what() << std::endl;
	}
	return students;
}

//std::vector<std::pair<int, std::string>> DatabaseConnection::selectStudents(const std::string& query)
//{
//	std::vector<std::pair<int, std::string>> results;
//	try {
//		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
//		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
//
//		while (res->next()) {
//			int id = res->getInt("id");
//			sql::SQLString full_name = res->getString("full_name");
//			results.emplace_back(id, full_name);
//		}
//	}
//	catch (sql::SQLException& e) {
//		std::cerr << "Query failed: " << query << "\nError: " << e.what() << std::endl;
//	}
//	return results;
//}

void DatabaseConnection::executeQuery(const std::string &query) {
	try {
		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
		stmt->execute(query);
	}
	catch (sql::SQLException &e) {
		std::cerr << "Query failed: " << query << std::endl;
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

