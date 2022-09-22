#include "database.h"
#include "assert.h"
using namespace std;

Database::Database(string file) {
    _exit = sqlite3_open(file.c_str(), &_DB);
    assert(_exit != 1);
}

Database::~Database() {
    sqlite3_close(_DB);
}

void Database::exec(string sql) {
    assert(_exit != 1);
    _exit = sqlite3_exec(_DB, sql.c_str(), nullptr, 0, nullptr);
}
