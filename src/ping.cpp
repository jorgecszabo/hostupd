#include "ping.h"

Ping::Ping(std::string host, std::string flags, std::string absPath): _host(host), _flags(flags), _path(absPath) {
    string command(_path + " " + _flags + " " + _host);

    char buffer[128];
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        _exitCode -1;
        return;
    }
    while (fgets(buffer, 128, pipe) != NULL) {
        _stdout += buffer;
    }
    _exitCode = pclose(pipe);

    string rtt = getRtt();

    size_t pos = 0;
    std::string token;
    int i = 0;
    float arr[4];
    while ((pos = rtt.find('/')) != std::string::npos) {
        token = rtt.substr(0, pos);
        arr[i] = stof(token);
        i++;
        rtt.erase(0, pos + 1);
    }
    _min = arr[0];
    _avg = arr[1];
    _max = arr[2];
    _mdev = arr[3];
}

int Ping::exitCode() {
    return _exitCode;
}

string Ping::stdout() {
    return _stdout;
}

float Ping::min() {
    return _min;
}

float Ping::max() {
    return _max;
}

float Ping::mdev() {
    return _mdev;
}

float Ping::avg() {
    return _avg;
}

string Ping::getRtt() {
    if (_exitCode != 0)
        return "";

    int i = 0;
    const char startPattern[] = "rtt min/avg/max/mdev = ";
    const char endPattern[] = " ms\n";

    size_t start = _stdout.find(startPattern);
    size_t end = _stdout.find(endPattern);

    return _stdout.substr(start + sizeof(startPattern) - 1, end - start - sizeof(startPattern) + 1);
}