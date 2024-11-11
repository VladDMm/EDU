#pragma once
#ifndef INCLUDES_FOR_EDU
#define INCLUDES_FOR_EDU

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <mariadb/conncpp.hpp>
#include <memory>

#include <openssl/evp.h>      // pentru operații de criptare și hash
#include <openssl/rand.h>     // pentru generare de numere aleatoare (ex., sare)
#include <openssl/sha.h>      // pentru hash-uri (ex., SHA-256)


#include <utility>  // for std::pair
#include <chrono>   // for std::chrono::system_clock
#include <iomanip>  // for std::put_time
#include <sstream>  // for std::stringstream

#include "DatabaseConnection.h"
#include "User.h"
#include "Student.h"
#include "Professor.h"
#include "Grupa.h"
#include "Absente.h"
#include "Nota.h"
#include "Curs.h"
#include "Catedra.h"
#include "SystemManagement.h"
#include "Admin.h"

extern DatabaseConnection db_conn;

#endif // !INCLUDES_FOR_EDU


