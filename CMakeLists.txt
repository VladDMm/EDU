cmake_minimum_required(VERSION 3.10)
project(EDU-Reusita)

set(CMAKE_CXX_STANDARD 17)

# Include paths for MariaDB Connector
set(MARIADB_CPP_INCLUDE_DIR "C:/Program Files/MariaDB/MariaDB C++ Connector 64-bit/include")
set(MARIADB_CPP_LIB_DIR "C:/Program Files/MariaDB/MariaDB C++ Connector 64-bit")

include_directories(${MARIADB_CPP_INCLUDE_DIR})
link_directories(${MARIADB_CPP_LIB_DIR})

# Define source files
add_executable(EDU-Reusita academic_records.cpp EDU-Reusita.cpp)

# Link with MariaDB library (mariadbcpp-static or mariadbcpp based on what you're using)
target_link_libraries(EDU-Reusita mariadbcpp-static)  # Sau mariadbcpp, dacă ai nevoie de versiunea DLL

# Copy mariadbcpp.dll next to the executable if using DLL version
if (WIN32)
    add_custom_command(TARGET EDU-Reusita POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MARIADB_CPP_LIB_DIR}/mariadbcpp.dll" $<TARGET_FILE_DIR:EDU-Reusita>)
endif()