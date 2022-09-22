#ifndef HOSTUPD_DATABASE_H
#define HOSTUPD_DATABASE_H
#include "sqlite3.h"
#include <string>

using namespace std;

class Database {
public:
    Database(string file);
    ~Database();
    void exec(string sql);
private:
    sqlite3* _DB;
    int _exit = -1;
};


#endif //HOSTUPD_DATABASE_H
