#ifndef HOSTUPD_CFGFILE_H
#define HOSTUPD_CFGFILE_H

#include <fstream>
#include <map>
#include <thread>
#include <vector>
#include "assert.h"
#include <string>

using namespace std;

void readConfigFile(map<string,string> &cfg);
int getSeconds(string s);
vector<string> parseHosts(const string &s);

#endif //HOSTUPD_CFGFILE_H
