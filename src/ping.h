//
// Created by jorge on 21/09/22.
//

#ifndef HOSTUPD_PING_H
#define HOSTUPD_PING_H
#include <string>

using namespace std;

class Ping {
public:
    Ping(string host, string flags, string absPath);
    string stdout();
    int exitCode();
    float min();
    float avg();
    float max();
    float mdev();
private:
    string getRtt();  //_exitCode must be zero
    float _min = 0.0;
    float _avg = 0.0;
    float _max = 0.0;
    float _mdev = 0.0;
    string _host;
    string _flags;
    string _path;
    string _stdout = "";
    int _exitCode = -1;
};

#endif //HOSTUPD_PING_H
