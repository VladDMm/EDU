//#include <algorithm>
//#include "academic_records.h"
//
//DatabaseConnection db_conn;
//
//DatabaseConnection::DatabaseConnection() 
//{
//	// Configurare conexiune
//	//sql::SQLString url("jdbc:mariadb://localhost:3306/academic_records");
//	sql::SQLString url("jdbc:mariadb://localhost:3306/EDU");
//	sql::Properties properties({ {"user", "root"}, {"password", "root"} });
//	// Conectează la baza de date
//	try {
//		driver = sql::mariadb::get_driver_instance();  // Obține driverul MariaDB
//		conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
//		//std::cout << "Conexiune reușită!" << std::endl;
//	}
//	catch (sql::SQLException &e) {
//		std::cerr << "Eroare de conexiune: " << e.what() << std::endl;
//	}
//}
//
//int DatabaseConnection::getLastInsertId()
//{
//	try
//	{
//		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
//		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT LAST_INSERT_ID()"));
//
//		if (res->next())
//		{
//			return res->getInt(1);
//		}
//		else
//		{
//			std::cerr << "Nu s-a putut obține ultimul ID inserat." << std::endl;
//			return -1;
//		}
//	}
//	catch (sql::SQLException &e)
//	{
//		std::cerr << "SQL Exception: " << e.what() << std::endl;
//		return -1;
//	}
//}
//
//int DatabaseConnection::getLastInsertId(const char *query)
//{
//	try
//	{
//		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
//		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
//
//		if (res->next())
//		{
//			return res->getInt(1);
//		}
//		else
//		{
//			std::cerr << "Nu s-a putut obține ultimul ID inserat." << std::endl;
//			return -1;
//		}
//	}
//	catch (sql::SQLException &e)
//	{
//		std::cerr << "SQL Exception: " << e.what() << std::endl;
//		return -1;
//	}
//}
//
//void DatabaseConnection::addGroupToDatabase(const std::string& groupName, int groupYear, int id_catedra)
//{
//	try
//	{
//		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO groups (group_name, study_year, department_id) VALUES (?, ?, ?)"));
//		pstmt->setString(1, groupName);
//		pstmt->setInt(2, groupYear);
//		pstmt->setInt(3, id_catedra);
//		pstmt->executeUpdate();
//		std::cout << "Grupa a fost adaugata cu succes in baza de date!" << std::endl;
//	}
//	catch (sql::SQLException &e)
//	{
//		std::cerr << "SQL Exception: " << e.what() << std::endl;
//	}
//}
//
//void DatabaseConnection::updateCatedra(int id, const std::string &newName)
//{
//	try
//	{
//		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("UPDATE departments SET department_name = ? WHERE department_id = ?"));
//		pstmt->setString(1, newName);
//
//		pstmt->setInt(2, id);
//		int affectedRows = pstmt->executeUpdate();
//
//		if (affectedRows > 0)
//		{
//			std::cout << "Catedra cu ID-ul " << id << " a fost actualizată cu succes." << std::endl;
//		}
//		else
//		{
//			std::cout << "Nu s-a găsit o catedră cu acest ID." << std::endl;
//		}
//	}
//	catch (sql::SQLException &e)
//	{
//		std::cerr << "SQL Exception: " << e.what() << std::endl;
//	}
//}
//
//void DatabaseConnection::displayGroups_from_bd()const
//{
//	const std::string query = "Select group_id, group_name, study_year FROM groups";
//	try {
//		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
//		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
//
//		while (res->next())
//		{
//			int id = res->getInt("group_id");
//			sql::SQLString name = res->getString("group_name");
//			int year_study = res->getInt("study_year");
//			std::cout << id << ": " << name << ", An studii: " << year_study << std::endl;
//		}
//	}
//	catch (sql::SQLException& e) {
//		std::cerr << "Query failed: " << query << "\nError: " << e.what() << std::endl;
//	}
//}
//
//std::vector<std::pair<int, std::string>> DatabaseConnection::selectDepartments(const std::string& query) {
//	std::vector<std::pair<int, std::string>> results;
//	try {
//		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
//		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
//
//		while (res->next()) 
//		{
//			int id = res->getInt("department_id");
//			sql::SQLString name = res->getString("department_name");
//			results.emplace_back(id, name);
//		}
//	}
//	catch (sql::SQLException& e) {
//		std::cerr << "Query failed: " << query << "\nError: " << e.what() << std::endl;
//	}
//	return results;
//}
//
//// Metodă pentru a obține lista de studenți
//std::vector<std::tuple<int, std::string, std::string, std::string, int>> DatabaseConnection::selectStudents() {
//	std::vector<std::tuple<int, std::string, std::string, std::string, int>> students;
//	try {
//		std::string query =
//			"SELECT s.student_id, u.fullname, u.email, u.username, s.group_id "
//			"FROM students s "
//			"JOIN users u ON s.user_id = u.user_id";
//		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
//		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
//
//		while (res->next()) {
//			int student_id = res->getInt("student_id");
//			sql::SQLString fullname = res->getString("fullname");
//			sql::SQLString email = res->getString("email");
//			sql::SQLString username = res->getString("username");
//			int group_id = res->getInt("group_id");
//			/*std::string fullname = res->getString("fullname");
//			std::string email = res->getString("email");
//			std::string username = res->getString("username");*/
//			
//			students.emplace_back(student_id, fullname, email, username, group_id);
//		}
//	}
//	catch (sql::SQLException &e) {
//		std::cerr << "SQL Exception: " << e.what() << std::endl;
//	}
//	return students;
//}
//
////std::vector<std::pair<int, std::string>> DatabaseConnection::selectStudents(const std::string& query)
////{
////	std::vector<std::pair<int, std::string>> results;
////	try {
////		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
////		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
////
////		while (res->next()) {
////			int id = res->getInt("id");
////			sql::SQLString full_name = res->getString("full_name");
////			results.emplace_back(id, full_name);
////		}
////	}
////	catch (sql::SQLException& e) {
////		std::cerr << "Query failed: " << query << "\nError: " << e.what() << std::endl;
////	}
////	return results;
////}
//
//void DatabaseConnection::executeQuery(const std::string &query) {
//	try {
//		std::unique_ptr<sql::Statement> stmt(conn->createStatement());
//		stmt->execute(query);
//	}
//	catch (sql::SQLException &e) {
//		std::cerr << "Query failed: " << query << std::endl;
//		std::cerr << "Error: " << e.what() << std::endl;
//	}
//}
//
///*------------------------Class Administrator---------------------------------*/
//
//void Administrator::show_menu()
//{
//	short option;
//	do
//	{
//		std::cout << "1. Adauga catedra" << std::endl;
//		std::cout << "2. Adauga grupa la catedra" << std::endl;
//		std::cout << "-. Adauga studenti la catedra" << std::endl;
//		std::cout << "4. Adauga profesori la catedra" << std::endl;
//		std::cout << "5. Adauga curs la catedra" << std::endl;
//		std::cout << "6. Adauga studenti la grupa" << std::endl;
//		std::cout << "7. Adauga studenti la curs" << std::endl;
//		std::cout << "8. Adauga profesori la curs" << std::endl;
//		std::cout << "9. Afiseaza catedre" << std::endl;
//		std::cout << "10. Sterge catedra" << std::endl;
//		std::cout << "11. Afisaeza toti studentii" << std::endl;
//		std::cout << "12. Afisaeza grupele" << std::endl;
//		std::cout << "0. Iesi" << std::endl;
//		std::cout << "Alege optiunea: " << std::endl;
//		std::cin >> option;
//
//		switch (option)
//		{
//		case 1:
//			sistem->add_catedra();
//			system("cls");
//			break;
//		case 2:
//			sistem->add_group_to_catedra();
//			system("cls");
//			break;
//		case 3:
//			//sistem->add_students_to_catedra();
//			system("cls");
//			break;
//		case 4:
//			sistem->add_professor_to_catedra();
//			system("cls");
//			break;
//		case 5:
//			sistem->add_courses_to_catedra();
//			system("cls");
//			break;
//		case 6:
//			sistem->add_students_to_group();
//			system("cls");
//			break;
//		case 7:
//			sistem->add_students_to_course();
//			system("cls");
//			break;
//		case 8:
//			sistem->add_professor_to_course();
//			system("cls");
//			break;
//		case 9:
//			sistem->display_catedre();
//			system("cls");
//			break;
//		case 10:
//			sistem->remove_catedra();
//			system("cls");
//			break;
//		case 11:
//			sistem->display_students_from_db();
//			break;
//		case 12:
//			sistem->display_groups();
//			break;
//		case 0:
//			system("cls");
//			std::cout << "La revedere!" << std::endl;
//			break;
//		default:
//			system("cls");
//			std::cout << "Nu este asa optiune!" << std::endl;
//			break;
//		}
//
//	} while (option != 0);
//
//}
//
///*----------------------End Class Administrator-----------------------------------*/
//
///*------------------------Class Student---------------------------------*/
//
//void Student::update_name()
//{
//	std::string new_name;
//	std::cout << "Introdu numele nou: ";
//	std::getline(std::cin, new_name);
//	full_name = new_name;
//}
//
//void Student::display_student() const
//{
//	std::cout  << "Nume: " << full_name;
//}
//
//size_t Student::get_id() const
//{
//	return id_student;
//}
//
//std::string Student::get_name() const 
//{
//	return full_name;
//}
//
////void Student::insert_into_db() const {
////	// Inserare în tabela users
////	std::string user_query = "INSERT INTO users (fullname, email, username, password_hash, salt, user_type) VALUES ('" + full_name + "', '" + email + "', '" + username + "', '" + password_hash + "', '" + salt + "', '" + std::to_string(user_type) + "')";
////	db_conn.executeQuery(user_query);
////
////	// Inserare în tabela students
////	std::string student_query = "INSERT INTO students (user_id, group_id) VALUES ('" + std::to_string(user_id) + "', '" + std::to_string(group_id) + "')";
////	db_conn.executeQuery(student_query);
////}
//
//void Student::insert_into_db() const {
//	// Inserare în tabela users
//	std::string user_query = "INSERT INTO users (fullname, email, username, password_hash, salt, user_type) "
//		"VALUES ('" + full_name + "', '" + email + "', '" + username + "', '" + password_hash + "', '" + salt + "', 'student')";
//	db_conn.executeQuery(user_query);
//
//	// Obține ID-ul generat automat pentru user
//	int new_user_id = db_conn.getLastInsertId("SELECT LAST_INSERT_ID() FROM `users`"); // Presupunând că există o metodă care obține `LAST_INSERT_ID()`
//
//	// Asigură-te că `new_user_id` este valid
//	if (new_user_id > 0)
//	{
//		// Inserare în tabela students
//		std::string student_query = "INSERT INTO students (user_id, group_id) VALUES (" + std::to_string(new_user_id) + ", " + std::to_string(group_id) + ")";
//		db_conn.executeQuery(student_query);
//	}
//	else {
//		std::cerr << "Eroare: nu s-a putut obține user_id-ul generat pentru user." << std::endl;
//	}
//}
//
//void Student::show_menu()
//{
//	// Obține instanța SystemManagement
//	SystemManagement *system = SystemManagement::getInstance();
//	// Apelează get_catedra_student pentru a obține catedra studentului curent
//	const Catedra* catedra = system->get_catedra_student(id_student);
//
//	short option;
//
//	do
//	{
//		std::cout << "1. Afisare cursuri la care esti inscris" << std::endl;
//		std::cout << "2. Afisare note" << std::endl;
//		std::cout << "3. Afisare absente" << std::endl;
//		std::cout << "0. Iesire" << std::endl;
//
//		std::cin >> option;
//
//		switch (option)
//		{
//		case 1:
//		{
//			if (!catedra)
//			{
//				std::cout << "Nu esti înscris la nicio catedră.\n";
//				break;
//			}
//			std::cout << "Afisare cursuri inscrise pentru catedra: " << catedra->get_name_catedra() << "\n";
//			catedra->show_student_courses(id_student);
//		}
//		break;
//		case 2:
//		{
//			
//			
//		}
//		break;
//		case 3:
//		{
//			
//		}
//		break;
//		case 0:
//			break;
//		default:
//			break;
//		}
//
//	} while (option != 0);
//
//}
//
///*----------------------End Class Student-----------------------------------*/
//
///*----------------------Class Profesor-----------------------------------*/
//
//void Profesor::show_menu()
//{
//	SystemManagement *system = SystemManagement::getInstance();
//
//	// Apelează get_catedra_profesor pentru a obtine catedra profesorului curent
//	Catedra *catedra = system->get_catedra_profesor(id_professor);
//
//	if (!catedra)
//	{
//		std::cout << "Nu esti inscris la nici o catedra" << std::endl;
//		return;
//	}
//
//	short option;
//	do
//	{
//		std::cout << "1. Afisare cursuri disponibile" << std::endl;
//		std::cout << "2. Afisare studenti la curs" << std::endl;
//		std::cout << "3. Adauga nota la curs" << std::endl;
//		std::cout << "4. Adauga absenta la curs" << std::endl;
//		std::cout << "5. Afisare note la curs" << std::endl;
//		std::cout << "6. Afisare absente la curs" << std::endl;
//		std::cout << "0. Iesi" << std::endl;
//
//		std::cin >> option;
//		std::cin.ignore();
//
//		switch (option)
//		{
//		case 1:
//		{
//			catedra->show_professor_courses(id_professor);
//			break;
//		}
//		case 2:
//		{
//			catedra->display_students_in_course_by_prof(id_professor);
//			break;
//		}
//		case 3:
//		{
//			catedra->add_grade_to_course(id_professor);
//			break;
//		}
//		case 4:
//		{
//			catedra->add_absence_to_course(id_professor);
//			break;
//		}
//		case 5:
//			catedra->display_grades_in_course(id_professor);
//			break;
//		case 6:
//			catedra->display_absence_in_course(id_professor);
//		case 0:
//			break;
//		default:
//			std::cout << "Alegere incorecta!" << std::endl;
//			break;
//		}
//	} while (option != 0);
//	
//}
//
//std::string Profesor::get_full_name() const
//{
//	return full_name;
//}
//
//size_t Profesor::get_id_prof()const
//{
//	return id_professor;
//}
//
//std::string Profesor::get_role() const
//{
//	return professor_role;
//}
//
//void Profesor::insert_into_db() const {
//	// Inserare în tabela users
//	std::string user_query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password_hash + "')";
//	db_conn.executeQuery(user_query);
//
//	// Inserare în tabela professors
//	std::string professor_query = "INSERT INTO professors (id, full_name, professor_role, username, password) VALUES ('" +
//		std::to_string(id_professor) + "', '" + full_name + "', '" + professor_role + "', '" + username + "', '" + password_hash + "')";
//	db_conn.executeQuery(professor_query);
//}
//
///*------------------------End Class Profesor---------------------------------*/
//
///*----------------------Class Grupa-----------------------------------*/
//
//void Grupa::add_student(std::vector<Student> &student_vector)
//{
//	students.insert(students.begin(), student_vector.begin(), student_vector.end());
//
//	for (const auto &student : student_vector)
//	{
//		student.insert_into_db();
//	}
//}
//
//void Grupa::add_student(std::map<size_t, Student>::iterator &it)
//{
//	
//	students.push_back(it->second);
//}
//
//void Grupa::remove_student(size_t student_id)
//{
//	students.erase(std::remove_if(students.begin(), students.end(),
//		[student_id](const Student& student) 
//	{ return student.get_id() == student_id; }), students.end());
//}
//
//void Grupa::display_group() const 
//{
//	db_conn.displayGroups_from_bd();
//}
//
//void Grupa::display_all_students() const
//{
//	for (const auto &x : students)
//	{
//		std::cout << x.get_name() << std::endl;
//	}
//}
//
//void Grupa::display_students_in_group() const
//{
//	std::cout << id_group <<": Grupa " << group_name << " (Anul " << year_of_study << ")\n";
//	for (const auto &x : students)
//	{
//		std::cout << x.get_name() << std::endl;
//	}
//}
//
//size_t Grupa::get_num_students() const
//{
//	return students.size();
//}
//
//size_t Grupa::get_id() const
//{
//	return id_group;
//}
//
//const std::vector<Student> Grupa::get_students() const
//{
//	return students;
//}
//
///*--------------------------End Class Grupa-------------------------------*/
//
///*---------------------------Class Nota-----------------------------------*/
//
//void Nota::add_grade(std::string name_course, Student &student, double grade) 
//{
//	auto now = std::chrono::system_clock::now();  // Obține timpul curent
//	this->course_name = name_course;
//	grades[student].emplace_back(grade, now);      // Adaugă nota cu data
//}
//
//double Nota::calculate_average(const Student& student) const 
//{
//	auto it = grades.find(student);
//	if (it != grades.end() && !it->second.empty()) {
//		double sum = 0;
//		for (const auto& nota : it->second) {
//			sum += nota.get_value();
//		}
//		return sum / it->second.size();
//	}
//	return 0.0;  // Returnează 0 dacă studentul nu are note
//}
//
//bool Nota::search_grade(const Student& student, double grade_to_search) const 
//{
//	auto it = grades.find(student);
//	if (it != grades.end()) {
//		for (const auto& nota : it->second) {
//			if (nota.get_value() == grade_to_search) {
//				return true;  // Nota a fost găsită
//			}
//		}
//	}
//	return false; // Nota nu a fost găsită
//}
//
//void Nota::display_grades() const 
//{
//	for (const auto& pair : grades) {
//		const Student& student = pair.first;
//		const std::vector<NotaDetaliata> &student_grades = pair.second;
//
//		std::cout << "Curs: " << course_name << std::endl;
//		std::cout << "Student: " << student.get_name() << " - Note: ";
//		for (const auto& nota : student_grades) 
//		{
//			std::cout << ": " << nota.get_value() << " (Date: " << nota.get_date() << ") ";
//		}
//		std::cout << std::endl;
//	}
//}
//
//
///*-------------------------End Class Nota--------------------------------*/
//
///*-------------------------Class Curs--------------------------------*/
//
////Curs Curs::get_course() const
////{
////	return Curs(id_course, course_name);
////}
//
//void Curs::insert_into_db() const {
//	std::string query = "INSERT INTO courses (id, course_name) VALUES (" +
//		std::to_string(id_course) + ", '" + course_name + "')";
//	db_conn.executeQuery(query);
//}
//
//void Curs::add_students(const std::vector<Student> &student_list)
//{
//	course_students.insert(course_students.end(), student_list.begin(), student_list.end());
//}
//
//void Curs::add_single_student(const Student &new_student)
//{
//	course_students.push_back(new_student);
//}
//
//void Curs::add_grade_for_student(std::string name_course, Student &student, double grade) {
//	nota.add_grade(name_course, student, grade); // Deleagă adăugarea notei către clasa Nota
//}
//
//void Curs::add_professor(Profesor &p_tmp)
//{
//	course_professors.push_back(p_tmp);
//}
//
//void Curs::remove_student(size_t id_student)
//{
//	course_students.erase(std::remove_if(course_students.begin(), course_students.end(),
//		[id_student](const Student& student) { return student.get_id() == id_student; }), course_students.end());
//}
//
//std::vector<size_t> Curs::get_id_students() const
//{
//	std::vector<size_t> ids;
//	for (const auto &student : course_students)
//		ids.push_back(student.get_id());
//	return ids;
//}
//
//std::vector<size_t> Curs::get_id_professors() const
//{
//	std::vector<size_t> ids;
//	for (const auto &prof : course_professors)
//		ids.push_back(prof.get_id_prof());
//	return ids;
//}
//
//void Curs::display_students_in_course()const
//{
//	if (course_students.empty())
//	{
//		std::cout << "Nu sunt studenti!\n";
//		return;
//	}
//	for (const auto &x : course_students)
//	{
//		x.display_student();
//	}
//}
//
//void Curs::display_professors_in_course()const
//{
//	for (const auto &profesor : course_professors)
//		std::cout << profesor.get_id_prof() << ": " << profesor.get_full_name()
//		<< " (" << profesor.get_role() << ")" << std::endl;
//}
//
//void Curs::display_students_absences() const
//{
//	absente.display_absence();
//}
//
//void Curs::display_course() const
//{
//	std::cout <<" Curs: " << course_name << "\n";
//}
//
//void Curs::display_students_grades() const
//{
//	nota.display_grades();
//}
//
////std::vector<Student> Curs::get_students() const
////{
////	return course_students;
////}
//
//size_t Curs::get_id()
//{
//	return id_course;
//}
//
//void Curs::add_absence_for_student(std::string &name_course, const Student &student, std::string &absence)
//{
//	absente.add_absence(name_course, student, absence);
//}
//
///*------------------------End Class Curs---------------------------------*/
//
///*------------------------Class Absente---------------------------------*/
//
//void Absente::add_absence(std::string &name_course, const Student &student, std::string &reason)
//{
//	auto now = std::chrono::system_clock::now();  // Obține timpul curent
//	this->course_name = name_course;
//	absences[student].emplace_back(reason, now);      // Adaugă absenta cu data
//}
//
//void Absente::display_absence() const
//{
//	for (const auto& pair : absences) {
//		const Student& student = pair.first;
//		const std::vector<AbsentaDetaliata> &student_absences = pair.second;
//
//		std::cout << "Curs: " << course_name << std::endl;
//		std::cout << "Student: " << student.get_name() << " - Absente: ";
//		for (const auto& nota : student_absences)
//		{
//			std::cout << ": " << nota.get_reason() << " (Date: " << nota.get_date() << ") ";
//		}
//		std::cout << std::endl;
//	}
//}
//
//void Absente::remove_absence(const Student &student)
//{
//
//}
//
///*----------------------End Class Absente-----------------------------------*/
///*----------------------Class Catedra-----------------------------------------*/
//
//void Catedra::insert_catedra_to_bd()
//{
//	std::string query = "INSERT INTO departments (department_name, faculty) VALUES ('" + catedra_name + "', '" + faculty + "')";
//	db_conn.executeQuery(query);
//}
//
////void Catedra::add_students()
////{
////	system("cls");
////	std::cin.ignore();
////	size_t student_id = 1;
////	std::string student_name;
////	if (!students.empty())
////	{
////		student_id = (--students.end())->first;
////		++student_id;
////		std::cout << "Pentru sfarsit apasa enter" << std::endl;
////		do
////		{
////			std::cout << "Introdu numele studentului: ";
////			std::getline(std::cin, student_name);
////
////			if (student_name.size() != 0)
////			{
////				std::string email, user, pass;
////				std::cout << "Introdu email-ul: ";
////				std::cin >> email;
////				std::cout << "Introdu username-ul: ";
////				std::cin >> user;
////				std::cout << "Introdu parola: ";
////				std::cin >> pass;
////
////				Student student_temp(student_id, student_name, user, pass);
////			//	students[student_id] = student_temp;
////				student_temp.insert_into_db();
////				++student_id;
////				std::cin.ignore();
////			}
////			else
////				break;
////
////		} while (true);
////	}
////
////	else
////	{
////		std::cout << "Pentru sfarsit apasa enter" << std::endl;
////		do
////		{
////			std::cout << "Introdu numele studentului: ";
////			std::getline(std::cin, student_name);
////
////			if (student_name.size() != 0)
////			{
////				std::string email, user, pass;
////				std::cout << "Introdu email-ul: ";
////				std::cin >> email;
////				std::cout << "Introdu username-ul: ";
////				std::cin >> user;
////				std::cout << "Introdu parola: ";
////				std::cin >> pass;
////
////				Student student_temp(student_id, student_name, user, pass);
////				//students[student_id] = student_temp;
////				student_temp.insert_into_db();
////				++student_id;
////				std::cin.ignore();
////
////			}
////			else
////				break;
////
////		} while (true);
////	}
////	
////}
//// Funcție pentru a adăuga un profesor
//
//void Catedra::add_professor()
//{
//	system("cls");
//	std::cin.ignore();
//	size_t professor_id = 1;
//	std::string professor_name;
//	std::string professor_role;
//	std::cout << "Pentru sfarsit apasa enter" << std::endl;
//
//	if (!professors.empty())
//	{
//		professor_id = (--professors.end())->first;
//		++professor_id;
//		do
//		{
//			std::cout << "Introdu numele profesorului: ";
//			std::getline(std::cin, professor_name);
//			if (professor_name.size() != 0)
//			{
//				std::string user, pass, email;
//
//				std::cout << "Introdu rolul profesorului (titular, asistent etc.): ";
//				std::getline(std::cin, professor_role);
//				std::cout << "Introdu email: ";
//				std::getline(std::cin, email);
//				std::cout << "Introdu username: ";
//				std::cin >> user;
//				std::cout << "Introdu parola: ";
//				std::cin >> pass;
//				std::cin.ignore();
//				// Creăm un obiect Profesor cu datele introduse
//				Profesor profesor_temp(professor_name, email, professor_role, user, pass);
//				//professors[professor_id] = profesor_temp;
//				profesor_temp.insert_into_db();
//				//++professor_id;
//			}
//			else
//				break;
//
//		} while (true);
//	}
//
//	else
//	{
//		do
//		{
//			std::cout << "Introdu numele profesorului: ";
//			std::getline(std::cin, professor_name);
//			if (professor_name.size() != 0)
//			{
//				std::string user, pass, email;
//
//				std::cout << "Introdu rolul profesorului (titular, asistent etc.): ";
//				std::getline(std::cin, professor_role);
//				std::cout << "Introdu email: ";
//				std::getline(std::cin, email);
//				std::cout << "Introdu username: ";
//				std::cin >> user;
//				std::cout << "Introdu parola: ";
//				std::cin >> pass;
//				std::cin.ignore();
//				// Creăm un obiect Profesor cu datele introduse
//				Profesor profesor_temp(professor_name, email, professor_role, user, pass);
//				//professors[professor_id] = profesor_temp;
//				profesor_temp.insert_into_db();
//				//++professor_id;
//			}
//			else
//				break;
//
//		} while (true);
//	}
//}
//
//void Catedra::add_course()
//{
//	system("cls");
//	std::cin.ignore();
//
//	size_t course_id = 1;
//	std::string course_name;
//
//	if (!course_prof_map.empty())
//	{
//		course_id = (--course_prof_map.end())->first;
//		++course_id;
//
//		std::cout << "Pentru sfarsit apasa enter" << std::endl;
//
//		do
//		{
//			std::cout << "Introdu nume curs: ";
//			std::getline(std::cin, course_name);
//			if (course_name.size() != 0)
//			{
//				Curs curs_temp(course_id, course_name);
//				curs_temp.insert_into_db();
//				course_prof_map[course_id] = curs_temp;
//				++course_id;
//			}
//			else
//				break;
//
//		} while (true);
//	}
//
//	else
//	{
//		std::cout << "Pentru sfarsit apasa enter" << std::endl;
//		do
//		{
//			std::cout << "Introdu nume curs: ";
//			std::getline(std::cin, course_name);
//			if (course_name.size() != 0)
//			{
//				Curs curs_temp(course_id, course_name);
//				course_prof_map[course_id] = curs_temp;
//				curs_temp.insert_into_db();
//				++course_id;
//			}
//			else
//				break;
//
//		} while (true);
//	}
//	
//}
//
//void Catedra::add_group()
//{
//
//	//if (!groups.empty())
//	//{
//	//	size_t group_id = (--groups.end())->first;
//	//	++group_id;
//	//	std::string group_name;
//	//	int group_year = 0;
//
//	//	std::cout << "Pentru sfarsit apasa enter" << std::endl;
//	//	do
//	//	{
//	//		std::cout << "Introdu denumirea grupei: ";
//	//		std::getline(std::cin, group_name);
//	//		if (!group_name.empty())
//	//		{
//	//			std::cout << "Introdu anul grupei: ";
//	//			std::cin >> group_year;
//	//			std::cin.ignore();
//	//			// Creăm obiectul de tip Grupa și îl adăugăm în map
//	//			Grupa group_temp(group_id, group_name, group_year);
//	//			
//	//			groups.emplace(group_id, group_temp);
//	//			++group_id;
//	//			std::cout << "Grupa a fost adaugata cu succes!\n";
//	//		}
//	//		else
//	//			break;
//
//	//	} while (true);
//	//}
//	//else
//	//{
//	//	size_t group_id = 1;
//	//	std::string group_name;
//	//	int group_year = 0;
//
//	//	std::cout << "Pentru sfarsit apasa enter" << std::endl;
//	//	do
//	//	{
//	//		std::cout << "Introdu denumirea grupei: ";
//	//		std::getline(std::cin, group_name);
//	//		if (!group_name.empty())
//	//		{
//	//			std::cout << "Introdu anul grupei: ";
//	//			std::cin >> group_year;
//	//			std::cin.ignore();
//	//			// Creăm obiectul de tip Grupa și îl adăugăm în map
//	//			Grupa group_temp(group_id, group_name, group_year);
//
//	//			groups.emplace(group_id, group_temp);
//	//			++group_id;
//	//			std::cout << "Grupa a fost adaugata cu succes!\n";
//	//		}
//	//		else
//	//			break;
//
//	//	} while (true);
//	//}
//	
//	system("cls");
//	std::cin.ignore();
//	int group_year;
//	std::string group_name;
//	std::cout << "Pentru sfarsit apasa enter" << std::endl;
//	do
//	{
//		std::cout << "Introdu denumirea grupei: ";
//		std::getline(std::cin, group_name);
//		if (!group_name.empty())
//		{
//			std::cout << "Introdu anul grupei: ";
//			std::cin >> group_year;
//			std::cin.ignore();
//
//			// Adăugăm grupul în baza de date
//			db_conn.addGroupToDatabase(group_name, group_year,id_catedra);
//		}
//		else
//			break;
//
//	} while (true);
//}
//
//void Catedra::add_students_to_group()
//{
//	system("cls");
//	std::cin.ignore();
//	//if (students.empty())
//	//{
//	//	std::cout << "Nu exista studenti!\n";
//	//	return;
//	//}
//	//for (const auto &group : groups)
//	//{
//	//	std::cout << group.first << ": ";
//	//	group.second.display_group();
//	//	std::cout << std::endl;
//	//}
//	db_conn.displayGroups_from_bd();
//
//	size_t group_id;
//	std::cout << "Introdu ID-ul grupei: ";
//	std::cin >> group_id;
//	std::cin.ignore();
//
//	/*if (groups.find(group_id) == groups.end()) {
//		std::cout << "Grupa cu acest ID nu există!\n";
//		return;
//	}*/
//
//	/*for (auto &x : students)
//	{
//		std::cout << x.first << ": ";
//		x.second.display_student();
//		std::cout << std::endl;
//	}*/
//
//	//size_t id;
//	//do
//	//{
//	//	std::cout << "Alege id-ul studentilor(pentru iesire apasa 0):" << std::endl;
//	//	std::cin >> id;
//	//	if (id == 0)
//	//		break;
//	//	auto it = students.find(id);
//	//	groups[group_id].add_student(it);
//	//} while (true);
//
//
//	//size_t student_id = db_conn.getLastInsertId("SELECT  LAST_INSERT_ID() FROM `students`");
//	std::string student_name;
//
//	std::cout << "Pentru sfarsit apasa enter" << std::endl;
//	do
//	{
//		std::cout << "Introdu numele studentului: ";
//		std::getline(std::cin, student_name);
//
//		if (student_name.size() != 0)
//		{
//			std::string email, user, pass;
//			std::cout << "Introdu email-ul: ";
//			std::cin >> email;
//			std::cout << "Introdu username-ul: ";
//			std::cin >> user;
//			std::cout << "Introdu parola: ";
//			std::cin >> pass;
//
//			Student student_temp(student_name, email, group_id, user, pass);
//			//students[student_id] = student_temp;
//			student_temp.insert_into_db();
//			//++student_id;
//			std::cin.ignore();
//
//		}
//		else
//			break;
//
//	} while (true);
//
//	/*std::vector<Student> students_in_group;
//	std::cout << "Pentru sfarsit apasa enter" << std::endl;
//	size_t student_id = db_conn.getLastInsertId("SELECT FROM `students` LAST_INSERT_ID()");
//	std::string student_name;
//
//	do
//	{
//		std::cout << "Introdu numele studentului: ";
//		std::getline(std::cin, student_name);
//		if (!student_name.empty())
//		{
//			students_in_group.emplace_back(student_id, student_name);
//			++student_id;
//		}
//		else
//			break;
//	} while (true);
//
//	groups[group_id].add_student(students_in_group);*/
//}
//
//void Catedra::add_professor_to_course()
//{
//	system("cls");
//	for (const auto &course_entry : course_prof_map)
//	{
//		std::cout << course_entry.first << ": ";
//		course_entry.second.display_course();
//	}
//
//	size_t course_id = 0;
//	std::cout << "Alege cursul: ";
//	std::cin >> course_id;
//	std::cin.ignore();
//
//	auto it_course = course_prof_map.find(course_id);
//	/*auto it = std::find_if(curs.begin(), curs.end(), [&](Curs &p)
//	{return p.get_id_curs() == id_curs; });*/
//
//	if (it_course == course_prof_map.end())
//	{
//		std::cout << "Nu exista un curs cu acest ID!" << std::endl;
//		return;
//	}
//
//	std::cout << "Cati profesori doresti sa adaugi la curs: ";
//	int num_professors;
//	std::cin >> num_professors;
//	std::cin.ignore();
//	std::cout << std::endl;
//
//	if (professors.empty())
//	{
//		std::cout << "Nu sunt profesori adaugati!" << std::endl;
//		return;
//	}
//	for (const auto &professor : professors)
//		std::cout << professor.second.get_id_prof() << ": " << professor.second.get_full_name() << std::endl;
//
//	int i = 0;
//	while (i < num_professors)
//	{
//		size_t professor_id = 0;
//		std::cout << "Alege profesorul: ";
//		std::cin >> professor_id;
//		std::cin.ignore();
//		std::cout << std::endl;
//		auto it_professor = professors.find(professor_id);
//		//auto it_professor = std::find_if(professors.begin(), professors.end(), [&](const Profesor &p)
//		//{return p.get_id() == professor_id; });
//
//		if (it_professor != professors.end())
//		{
//			it_course->second.add_professor(it_professor->second);
//		}
//		++i;
//	}
//	std::cout << "Profesori adaugati cu succes!";
//}
//
//void Catedra::add_students_to_course()
//{
//	system("cls");
//
//	if (course_prof_map.empty()) {
//		std::cout << "Nu sunt cursuri disponibile pentru adăugarea de studenți.\n";
//		return;
//	}
//
//	// Afișează cursurile disponibile
//	std::cout << "Cursurile disponibile:\n";
//	for (const auto& curs_entry : course_prof_map) {
//		std::cout << "ID Curs: " << curs_entry.first << "\n";
//		curs_entry.second.display_course();  // Metoda pentru afiaarea detaliilor cursului
//	}
//
//	size_t course_id = 0;
//	std::cout << "Alege ID-ul cursului la care dorești să adaugi studenți: ";
//	std::cin >> course_id;
//	std::cin.ignore();
//
//	// Caută cursul în mapa profesori_curs
//	auto course_it = course_prof_map.find(course_id);
//	if (course_it == course_prof_map.end()) 
//	{
//		std::cout << "Nu există un curs cu acest ID.\n";
//		return;
//	}
//
//	if (groups.empty())
//	{
//		std::cout << "Nu sunt studenți disponibili în grupe.\n";
//		return;
//	}
//
//	// Afișează studenții din fiecare grupă
//	std::cout << "Studenții disponibili:\n";
//	for (const auto& grupa_entry : groups) 
//	{
//		std::cout << "Grupa " << grupa_entry.first << ":\n";
//		grupa_entry.second.display_students_in_group();  // Metodă pentru afișarea studenților din grupă
//	}
//
//	size_t group_id = 0;
//	std::cout << "Alege ID-ul grupei de unde dorești să adaugi studenți: ";
//	std::cin >> group_id;
//	std::cin.ignore();
//
//	// Cauta grupa in mapa grupe
//	auto group_it = groups.find(group_id);
//	if (group_it == groups.end()) 
//	{
//		std::cout << "Nu s-a găsit grupa cu acest ID.\n";
//		return;
//	}
//	
//	const Grupa& grupa = group_it->second;
//	// Obține studentii din grupa
//	auto studenti = grupa.get_students();
//	course_it->second.add_students(studenti);
//
//	// Adauga studentii la cursul selectat
//	//for (const auto &student : studenti)
//	//{
//	//	course_it->second.add_single_student(student); // Metoda pentru a adauga un student la curs
//	//}
//
//	std::cout << "Studenți adăugați la cursul selectat.\n";
//}
//
//void Catedra::add_absence_to_course(size_t id_prof)
//{
//	system("cls");
//	this->show_professor_courses(id_prof);
//
//	std::cout << "Introdu ID-ul cursului: ";
//	short course_id;
//	std::cin >> course_id;
//	std::cin.ignore();
//
//	auto course_it = course_prof_map.find(course_id);
//	if (course_it == course_prof_map.end())
//	{
//		std::cout << "Nu este asa id la curs" << std::endl;
//		return;
//	}
//
//	for (auto &x : course_prof_map)
//	{
//		std::cout << x.first << ": ";
//		x.second.display_students_in_course();
//		std::cout << std::endl;
//	}
//	// Solicităm ID-ul studentului
//	std::cout << "Introduceți ID-ul studentului: ";
//	size_t student_id;
//	std::cin >> student_id;
//	std::cin.ignore();
//
//	// Căutăm studentul în sistem
//	auto student_it = students.find(student_id);
//	if (student_it == students.end()) {
//		std::cout << "Studentul cu ID-ul " << student_id << " nu a fost găsit.\n";
//		return;
//	}
//
//	std::cout << "Absenta a-absent/m-motivat" << std::endl;
//	std::string absence;
//	std::cin >> absence;
//
//	Student& student = student_it->second;
//	std::string name_cours = course_it->second.get_name_course();
//
//	course_it->second.add_absence_for_student(name_cours, student, absence);
//
//	std::cout << "Absenta a fost adaugata!" << std::endl;
//}
//
//void Catedra::add_grade_to_course(size_t id_prof)
//{
//	system("cls");
//	this->show_professor_courses(id_prof);
//
//	size_t course_id, student_id;
//	double grade_value;
//
//	// Solicităm ID-ul cursului
//	std::cout << "Introduceți ID-ul cursului: ";
//	std::cin >> course_id;
//
//	// Căutăm cursul după ID
//	auto course_it = course_prof_map.find(course_id);
//	if (course_it == course_prof_map.end()) {
//		std::cout << "Cursul cu ID-ul " << course_id << " nu a fost găsit.\n";
//		return;
//	}
//
//	for (auto &x : course_prof_map)
//	{
//		std::cout << x.first << ": ";
//		x.second.display_students_in_course();
//		std::cout << std::endl;
//	}
//	// Solicităm ID-ul studentului
//	std::cout << "Introduceți ID-ul studentului: ";
//
//	std::cin >> student_id;
//	std::cin.ignore();
//
//	// Căutăm studentul în sistem
//	auto student_it = students.find(student_id);
//	if (student_it == students.end()) {
//		std::cout << "Studentul cu ID-ul " << student_id << " nu a fost găsit.\n";
//		return;
//	}
//
//	// Solicităm valoarea notei
//	std::cout << "Introduceți nota: ";
//	std::cin >> grade_value;
//	std::cin.ignore();
//
//	// Adăugăm nota pentru studentul specificat în cursul selectat
//	Student& student = student_it->second;
//	std::string name_cours = course_it->second.get_name_course();
//	course_it->second.add_grade_for_student(name_cours, student, grade_value);
//
//	std::cout << "Nota a fost adăugată cu succes!\n";
//}
//
//void Catedra::display_absence_in_course(size_t id_prof)
//{
//	system("cls");
//	this->show_professor_courses(id_prof);
//
//	std::cout << "Alege cursul: ";
//	short course_id;
//	std::cin >> course_id;
//
//	auto it_course = course_prof_map.find(course_id);
//	if (it_course == course_prof_map.end())
//	{
//		std::cout << "Nu este asa id la curs" << std::endl;
//		return;
//	}
//
//	it_course->second.display_students_absences();
//}
//
//// Funcție pentru a afișa toate grupele
//void Catedra::display_groups() const
//{
//	system("cls");
//	//if (groups.empty()) {
//	//	std::cout << "Nu există grupe în sistem.\n";
//	//}
//	//else {
//	//	std::cout << "Lista grupelor:\n";
//	//	for (const auto& grupa_entry : groups) {
//	//		const Grupa& group_obj = grupa_entry.second;
//	//		// Afișează informațiile despre grupă
//	//		group_obj.display_group();
//	//		std::cout << std::endl;
//	//	}
//	//}
//
//	db_conn.displayGroups_from_bd();
//}
//
//void Catedra::display_grades_in_course(size_t id_prof) const 
//{
//	system("cls");
//	this->show_professor_courses(id_prof);
//
//	std::cout << "Alege cursul: ";
//	short course_id;
//	std::cin >> course_id;
//
//	auto it_course = course_prof_map.find(course_id);
//	if (it_course == course_prof_map.end())
//	{
//		std::cout << "Nu este asa id la curs" << std::endl;
//		return;
//	}
//
//	it_course->second.display_students_grades();
//}
//
//// Funcție pentru a afișa toți studenții
//void Catedra::display_students() const
//{
//	//if (groups.empty())
//	//{
//	//	std::cout << "Nu sunt studenti.";
//	//	return;
//	//}
//	//bool find_students = false;
//	//for (const auto &group_entry : groups)
//	//{
//	//	const Grupa& group_obj = group_entry.second;
//	//	// Verifică dacă grupa are studenți
//	//	if (group_obj.get_num_students() > 0)
//	//	{
//	//		std::cout << "Grupa " << group_entry.first << ":\n";  // Afișează ID-ul grupei
//	//		group_obj.display_group();
//	//		group_obj.display_all_students();  // Afișează studenții din această grupă
//	//		find_students = true;
//	//	}
//	//}
//	//// Dacă nu a fost găsit niciun student în nicio grupă
//	//if (!find_students)
//	//{
//	//	std::cout << "Nu sunt studenți în nicio grupă.\n";
//	//}
//
//	system("cls");
//
//
//}
//
//void Catedra::show_professor_courses(size_t id_profesor) const
//{
//	for (const auto &x : course_prof_map)
//	{
//		// Obține lista de ID-uri ale profesorilor din curs
//		std::vector<size_t> professor_ids = x.second.get_id_professors();
//		
//		// Verifică dacă ID-ul profesorului se află în lista de ID-uri
//		if (std::find(professor_ids.begin(), professor_ids.end(), id_profesor) != professor_ids.end())
//		{
//			std::cout << x.first << ": ";
//			// Afișează detalii despre curs dacă profesorul este înscris la acest curs
//			x.second.display_course();
//		}
//	}
//}
//
//// Afiseaza cursurile pentru studentul specific, functie pentru studenti
//void Catedra::show_student_courses(size_t id_student) const
//{
//	for (const auto &x : course_prof_map)
//	{
//		// Obține lista de ID-uri ale studenților din curs
//		std::vector<size_t> student_ids = x.second.get_id_students();
//
//		// Verifică dacă ID-ul studentului se află în lista de ID-uri
//		if (std::find(student_ids.begin(), student_ids.end(), id_student) != student_ids.end())
//		{
//			// Afișează detalii despre curs dacă studentul este înscris la acest curs
//			x.second.display_course();
//		}
//	}
//}
//
//// Funcție pentru a afișa toți profesorii
//void Catedra::display_professors() const
//{
//	system("cls");
//	if (professors.empty()) {
//		std::cout << "Nu există profesori în sistem.\n";
//	}
//	else {
//		std::cout << "Lista profesorilor:\n";
//		for (const auto& profesor : professors) {
//			std::cout << profesor.second.get_id_prof() << ": " <<
//				profesor.second.get_full_name() << " (" << profesor.second.get_role() << ")" << std::endl;
//		}
//	}
//}
//
//void Catedra::display_students_in_group() const
//{
//	system("cls");
//
//	if (groups.empty()) {
//		std::cout << "Nu sunt grupe disponibile.\n";
//		return;
//	}
//
//	std::cout << "Alege grupa:" << std::endl;
//	for (const auto &group_entry : groups)
//	{
//		std::cout << "ID Grupa: " << group_entry.first << std::endl; 
//		group_entry.second.display_group();
//		std::cout << std::endl;
//	}
//	short id_group = 0;
//	std::cin >> id_group;
//
//	// Verifică dacă grupa există
//	auto group_it = groups.find(id_group);
//	if (group_it == groups.end()) {
//		std::cout << "Nu există o grupă cu acest ID.\n";
//		return;
//	}
//	if (group_it->second.get_num_students() == 0)
//	{
//		std::cout << "Nu există studenti in aceasta grupa." << std::endl;
//		return;
//	}
//	// Afișează studenții din grupa selectată
//	//const Grupa& group_obj = group_it->second;
//	std::cout << "Studenții din grupa " << id_group << ":\n";
//	group_it->second.display_students_in_group();
//}
//
//// Afisare studentii de la curs dupa cursurile care ii apartin profesorului
//void Catedra::display_students_in_course_by_prof(size_t id_prof) const
//{
//	system("cls");
//	this->show_professor_courses(id_prof);
//
//	std::cout << "Alege cursul:\n";
//	short id_course;
//	std::cin >> id_course;
//	std::cin.ignore();
//
//	auto course_it = course_prof_map.find(id_course);
//	if (course_it == course_prof_map.end())
//	{
//		std::cout << "Nu este asa curs" << std::endl;
//		return;
//	}
//
//	course_it->second.display_students_in_course();
//
//
//	//short option;
//	//do
//	//{
//	//	std::cout << "1. Afisare studenti la curs" << std::endl;
//	//	std::cout << "2. Adauga nota la curs" << std::endl;
//	//	std::cout << "3. Adauga absenta la curs" << std::endl;
//	//	std::cout << "0. Iesi" << std::endl;
//	//	std::cin >> option;
//	//	switch (option)
//	//	{
//	//	case 1:
//	//	{
//	//		short id;
//	//		std::cin >> id;
//	//		auto it_course = course_prof_map.find(id);
//	//		if (it_course == course_prof_map.end())
//	//		{
//	//			std::cout << "Id incorect" << std::endl;
//	//			return;
//	//		}
//	//		it_course->second.display_students_in_course();
//	//		break;
//	//	}
//	//	case 2:
//	//	{
//	//		break;
//	//	}
//	//	case 3:
//	//	{
//	//		break;
//	//	}
//	//	case 0:
//	//		break;
//	//	default:
//	//		std::cout << "Alegere incorecta" << std::endl;
//	//		break;
//	//	}
//	//} while (option != 0);	
//}
//
//// Afisarea studentilor dupa cursurile selectate, functie pentru admin
//void Catedra::display_students_in_course() const
//{
//	system("cls");
//
//	for (const auto &course_entry : course_prof_map)
//	{
//		course_entry.second.display_course();
//	}
//
//	std::cout << "Alege cursul:\n";
//	short id_course;
//	std::cin >> id_course;
//	std::cin.ignore();
//
//	auto course_it = course_prof_map.find(id_course);
//	if (course_it == course_prof_map.end())
//	{
//		std::cout << "Nu este asa curs" << std::endl;
//		return;
//	}
//
//	course_it->second.display_students_in_course();
//}
//
//// Afisarea profesorilor dupa cursurile selectate, functie pentru admin
//void Catedra::display_professors_in_course() const
//{
//	system("cls");
//	std::cout << "Alege cursul:\n";
//	short id_course;
//	std::cin >> id_course;
//	std::cin.ignore();
//
//	auto it_professor = course_prof_map.find(id_course);
//	if (it_professor == course_prof_map.end())
//	{
//		std::cout << "Nu este asa curs" << std::endl;
//		return;
//	}
//	it_professor->second.display_professors_in_course();
//}
//
//// Verifică dacă un student este în această catedră
//bool Catedra::has_student(size_t id_student) const {
//	return students.find(id_student) != students.end();
//}
//// Verifica daca un profesor este in aceasta catedra
//bool Catedra::has_professor(size_t id_profesor) const
//{
//	return professors.find(id_profesor) != professors.end();
//}
//
//Student* Catedra::authenticate_student(std::string &usern, std::string &pass)
//{
//	for (auto &pair : students)
//	{
//		if (pair.second.get_username() == usern && pair.second.get_passw() == pass)
//			return &(pair.second);
//	}
//	return nullptr; // daca nu se găseste studentul
//}
//
//Profesor* Catedra::authenticate_profesor(std::string &user, std::string &pass)
//{
//	for (auto &pair : professors)
//	{
//		if (pair.second.get_username() == user && pair.second.get_passw() == pass)
//			return &(pair.second);
//	}
//	return nullptr; // daca nu se găseste proful
//}
//
///*----------------------End Class Catedra-----------------------------------------*/
//
///*----------------------Class SystemManagement-----------------------------------*/
//
//void SystemManagement::display_students_from_db()
//{
//	//std::string query = "SELECT user_id, full_name FROM users";
//	auto students = db_conn.selectStudents();
//
//	std::cout << "ID\tFull Name\tEmail\t\tUsername\tGroup ID\n";
//	std::cout << "-----------------------------------------------------------------------\n";
//	for (const auto& student : students) {
//		int student_id;
//		std::string fullname, email, username, password;
//		int group_id;
//		
//		// Destructurează tuple-ul
//		std::tie(student_id, fullname, email, username, group_id) = student;
//
//		// Afișează informațiile
//		std::cout << student_id << "\t\t" << fullname << "\t" << email << "\t"
//			<< username << "\t\t\t" << group_id << "\n";
//	}
//}
//
//void SystemManagement::display_catedre() const
//{
//	std::string query = "Select department_id, department_name FROM departments";
//
//	std::vector<std::pair<int, std::string>> catedre = db_conn.selectDepartments(query);
//
//	for (const auto &catedra : catedre)
//		std::cout << "ID: " << catedra.first << ", " << catedra.second << std::endl;
//}
//
//void SystemManagement::add_catedra()
//{
//	system("cls");
//	std::cin.ignore();
//	std::cout << "Pentru sfarsit apasa enter" << std::endl;
//	short id = 1;
//
//	if (!catedre.empty())
//	{
//		id = (--catedre.end())->first;
//		++id;
//		do
//		{
//			std::cout << "Introdu nume catedra: ";
//			std::string nume_catedra;
//			std::getline(std::cin, nume_catedra);
//			if (!nume_catedra.empty())
//			{
//				std::string faculty;
//				std::cout << "Introdu facultatea: ";
//				std::getline(std::cin, faculty);
//
//				Catedra temp(id, nume_catedra, faculty);
//				catedre[id] = temp;
//				temp.insert_catedra_to_bd();
//				++id;
//			}
//			else
//				break;
//
//		} while (true);
//	}
//
//	else
//	{
//		do
//		{
//			std::cout << "Introdu nume catedra: ";
//			std::string nume_catedra;
//			std::getline(std::cin, nume_catedra);
//			if (!nume_catedra.empty())
//			{
//				std::string faculty;
//				std::cout << "Introdu facultatea: ";
//				std::getline(std::cin, faculty);
//
//				Catedra temp(id, nume_catedra, faculty);
//				catedre[id] = temp;
//				temp.insert_catedra_to_bd();
//				++id;
//			}
//			else
//				break;
//
//		} while (true);
//	}
//	
//
//}
//
//void SystemManagement::remove_catedra()
//{
//	system("cls");
//
//	this->display_catedre();
//
//	std::cout << "Introdu id catedra: ";
//	int id_catedra;
//	std::cin >> id_catedra;
//	std::cin.ignore();
//
//	std::string query = "DELETE FROM departments WHERE department_id = id_catedra";
//	db_conn.executeQuery(query);
//
//	auto catedra_it = catedre.find(id_catedra);
//	if (catedra_it == catedre.end())
//	{
//		std::cout << "nu este asa catedra" << std::endl;
//		return;
//	}
//	catedre.erase(catedra_it);
//	std::cout << "catedra " << id_catedra << " a fost stearsa cu succes" << std::endl;
//}
//
////
////void SystemManagement::display_catedre() const
////{
////	system("cls");
////	for (const auto catedra_entry : catedre)
////	{
////		std::cout << catedra_entry.first << ": " 
////			<< catedra_entry.second.get_name_catedra() << std::endl;
////	}
////}
//// Implementare actualizare informatii catedra
//
//void SystemManagement::update_info_catedra() {
//	system("cls");
//
//	this->display_catedre();
//
//	size_t id;
//	std::cout << "Introdu ID-ul catedrei pe care vrei sa o actualizezi: ";
//	std::cin >> id;
//	std::cin.ignore();
//
//	auto it = catedre.find(id);
//	if (it == catedre.end()) {
//		std::cout << "Catedra nu exista!\n";
//		return;
//	}
//
//	std::cout << "Introdu nume nou" << std::endl;
//	std::string new_name;
//	std::getline(std::cin, new_name);
//
//	db_conn.updateCatedra(id, new_name);
//}
//
////void SystemManagement::add_group()
////{
////	this->display_catedre();
////
////	unsigned short id_catedra;
////	std::cout << "Introdu ID-ul catedrei: ";
////	std::cin >> id_catedra;
////	auto it = catedre.find(id_catedra); // Caută catedra
////	if (it == catedre.end()) {
////		std::cout << "Catedra cu ID-ul " << id_catedra << " nu a fost găsită.\n";
////		return;
////	}
////	it->second.add_group();
////}
//
//// nu folosita
//void SystemManagement::add_group_to_catedra()
//{
//	for (const auto &x : catedre)
//		std::cout << x.first << ": " <<
//		x.second.get_name_catedra() << std::endl;
//	unsigned short id_catedra;
//	std::cout << "Introdu ID-ul catedrei: ";
//	std::cin >> id_catedra;
//	auto it = catedre.find(id_catedra); // Caută catedra
//	if (it == catedre.end()) {
//		std::cout << "Catedra cu ID-ul " << id_catedra << " nu a fost găsită.\n";
//		return;
//	}
//	it->second.add_group();
//
//}
//
////void SystemManagement::add_students_to_catedra()
////{
////	system("cls");
////
////	for (const auto &x : catedre)
////		std::cout << x.first << ": " <<
////		x.second.get_name_catedra() << std::endl;
////
////	std::cout << "Introdu id-ul catedra: ";
////	size_t catedra_id;
////	std::cin >> catedra_id;
////
////	auto it_catedra = catedre.find(catedra_id);
////	
////	if (it_catedra != catedre.end())
////	{
////		it_catedra->second.add_students_to_group();
////		std::cout << "Studenti adaugati cu succes" << std::endl;
////	}
////	
////}
//
//void SystemManagement::add_professor_to_catedra()
//{
//	system("cls");
//
//	for (const auto &x : catedre)
//		std::cout << x.first << ": " <<
//		x.second.get_name_catedra() << std::endl;
//
//	std::cout << "Introdu id-ul catedra: ";
//	size_t catedra_id;
//	std::cin >> catedra_id;
//
//	auto it_catedra = catedre.find(catedra_id);
//
//	if (it_catedra != catedre.end())
//	{
//		it_catedra->second.add_professor();
//		std::cout << "Profesori adaugati cu succes" << std::endl;
//	}
//}
//
//void SystemManagement::add_courses_to_catedra()
//{
//	system("cls");
//
//	for (const auto &x : catedre)
//		std::cout << x.first << ": " <<
//		x.second.get_name_catedra() << std::endl;
//
//	std::cout << "Introdu id-ul catedra: ";
//	size_t catedra_id;
//	std::cin >> catedra_id;
//
//	auto it_catedra = catedre.find(catedra_id);
//
//	if (it_catedra != catedre.end())
//	{
//		it_catedra->second.add_course();
//		std::cout << "Cursuri adaugate cu succes" << std::endl;
//	}
//}
//
//void SystemManagement::add_students_to_group()
//{
//	/*system("cls");
//
//	for (const auto &x : catedre)
//		std::cout << x.first << ": " <<
//		x.second.get_name_catedra() << std::endl;
//
//	std::cout << "Introdu id-ul catedra: ";
//	size_t catedra_id;
//	std::cin >> catedra_id;
//
//	auto it_catedra = catedre.find(catedra_id);
//
//	if (it_catedra != catedre.end())
//	{
//		it_catedra->second.add_students_to_group();
//		std::cout << "Studenti adaugati cu succes" << std::endl;
//	}*/
//
//	system("cls");
//
//	for (const auto &x : catedre)
//		std::cout << x.first << ": " <<
//		x.second.get_name_catedra() << std::endl;
//
//	std::cout << "Introdu id-ul catedra: ";
//	size_t catedra_id;
//	std::cin >> catedra_id;
//
//	auto it_catedra = catedre.find(catedra_id);
//
//	if (it_catedra != catedre.end())
//	{
//		it_catedra->second.add_students_to_group();
//		std::cout << "Studenti adaugati cu succes" << std::endl;
//
//	}
//}
//
//void SystemManagement::add_students_to_course()
//{
//	system("cls");
//
//	for (const auto &x : catedre)
//		std::cout << x.first << ": " <<
//		x.second.get_name_catedra() << std::endl;
//
//	std::cout << "Introdu id-ul catedra: ";
//	size_t catedra_id;
//	std::cin >> catedra_id;
//
//	auto it_catedra = catedre.find(catedra_id);
//
//	if (it_catedra != catedre.end())
//	{
//		it_catedra->second.add_students_to_course();
//		std::cout << "Studenti adaugati cu succes" << std::endl;
//	}
//}
//
//void SystemManagement::add_professor_to_course()
//{
//	system("cls");
//
//	for (const auto &x : catedre)
//		std::cout << x.first << ": " <<
//		x.second.get_name_catedra() << std::endl;
//
//	std::cout << "Introdu id-ul catedra: ";
//	size_t catedra_id;
//	std::cin >> catedra_id;
//
//	auto it_catedra = catedre.find(catedra_id);
//
//	if (it_catedra != catedre.end())
//	{
//		it_catedra->second.add_professor_to_course();
//		std::cout << "Profesori adaugati cu succes" << std::endl;
//	}
//}
//
//const Catedra* SystemManagement::get_catedra_student(size_t id_student)
//{
//	for (const auto& catedra_pair : catedre)
//	{
//		const Catedra& catedra = catedra_pair.second;
//		if (catedra.has_student(id_student))
//		{ // Verifică dacă studentul este în catedră
//			return &catedra; // Returnează pointer către catedra găsită
//		}
//	}
//	return nullptr; // Returneaza nullptr daca studentul nu este gasit in nicio catedra
//}
//
//Catedra* SystemManagement::get_catedra_profesor(size_t id_profesor)
//{
//	for (auto& catedra_pair : catedre)
//	{
//		Catedra& catedra = catedra_pair.second;
//		if (catedra.has_professor(id_profesor))
//		{ // Verifica dacă prof-ul este in catedra
//			return &catedra; // Returneaza pointer catre catedra gasita
//		}
//	}
//	return nullptr; // Returneaza nullptr daca studentul nu este gasit in nicio catedra
//}
//
//std::map<size_t, Catedra>& SystemManagement::get_catedre()
//{
//	return catedre;
//}
//
//SystemManagement* SystemManagement::getInstance() {
//	if (instance == nullptr) {
//		instance = new SystemManagement();
//	}
//	return instance;
//}
//
//void SystemManagement::display_students() const
//{
//	system("cls");
//	for (const auto &pair : catedre)
//		std::cout << pair.first << ": "
//		<< pair.second.get_name_catedra();
//
//	std::cout << "Alege catedra: ";
//	short id_catedra;
//	std::cin >> id_catedra;
//
//	auto it_catedra = catedre.find(id_catedra);
//	if (it_catedra == catedre.end())
//	{
//		std::cout << "Nu este asa catedra!";
//	}
//
//	it_catedra->second.display_students();
//}
//
//void SystemManagement::display_professors() const
//{
//	system("cls");
//	
//	for (const auto &pair : catedre)
//		std::cout << pair.first << ": "
//		<< pair.second.get_name_catedra();
//
//	std::cout << "Alege catedra: ";
//	short id_catedra;
//	std::cin >> id_catedra;
//
//	auto it_catedra = catedre.find(id_catedra);
//	if (it_catedra == catedre.end())
//	{
//		std::cout << "Nu este asa catedra!";
//	}
//
//	it_catedra->second.display_professors();
//}
//
//void SystemManagement::display_students_in_group() const
//{
//	system("cls");
//
//	for (const auto &pair : catedre)
//		std::cout << pair.first << ": "
//		<< pair.second.get_name_catedra();
//
//	std::cout << "Alege catedra: ";
//	short id_catedra;
//	std::cin >> id_catedra;
//
//	auto it_catedra = catedre.find(id_catedra);
//	if (it_catedra == catedre.end())
//	{
//		std::cout << "Nu este asa catedra!";
//	}
//	
//	it_catedra->second.display_students_in_group();
//}
//
//void SystemManagement::display_students_in_course() const
//{
//	system("cls");
//
//	for (const auto &pair : catedre)
//		std::cout << pair.first << ": "
//		<< pair.second.get_name_catedra();
//
//	std::cout << "Alege catedra: ";
//	short id_catedra;
//	std::cin >> id_catedra;
//
//	auto it_catedra = catedre.find(id_catedra);
//	if (it_catedra == catedre.end())
//	{
//		std::cout << "Nu este asa catedra!";
//	}
//
//	it_catedra->second.display_students_in_course();
//}
//
//void SystemManagement::display_professors_in_course() const
//{
//	system("cls");
//
//	for (const auto &pair : catedre)
//		std::cout << pair.first << ": "
//		<< pair.second.get_name_catedra();
//
//	std::cout << "Alege catedra: ";
//	short id_catedra;
//	std::cin >> id_catedra;
//
//	auto it_catedra = catedre.find(id_catedra);
//	if (it_catedra == catedre.end())
//	{
//		std::cout << "Nu este asa catedra!";
//	}
//
//	it_catedra->second.display_professors_in_course();
//}
//
//void SystemManagement::display_groups() const
//{
//	system("cls");
//	
//	for (const auto &pair : catedre)
//		std::cout << pair.first << ": "
//		<< pair.second.get_name_catedra();
//
//	std::cout << "Alege catedra: ";
//	short id_catedra;
//	std::cin >> id_catedra;
//
//	auto it_catedra = catedre.find(id_catedra);
//	if (it_catedra == catedre.end())
//	{
//		std::cout << "Nu este asa catedra!";
//	}
//
//	it_catedra->second.display_groups();
//}
//
///*------------------------End Class SystemManagement---------------------------------*/