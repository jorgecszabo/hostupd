project(hostupd)

set(CMAKE_CXX_STANDARD 14)

add_executable(hostupd src/main.cpp src/ping.cpp src/ping.h src/cfgfile.h src/cfgfile.cpp 
	lib/sqlite3/sqlite3.h
        lib/sqlite3/sqlite3.c
        src/database.cpp src/database.h)

