cmake_minimum_required(VERSION 3.23)
project(hostupd)

set(CMAKE_CXX_STANDARD 14)

#set (LIB_DIR_LOCATION ${NAME}/lib)
#find_library(SQLite3 NAMES sqlite3 PATHS ${LIB_DIR_LOCATION})
#set(INCLUDE_DIRS ${NAME}/include)

#target_link_libraries(hostupd SQLite3)
#target_include_directories(hostupd PRIVATE ${INCLUDE_DIRS})
add_executable(hostupd src/main.cpp src/ping.cpp src/ping.h src/cfgfile.h src/cfgfile.cpp lib/sqlite3/sqlite3.h
        lib/sqlite3/sqlite3.c
        src/database.cpp src/database.h)

