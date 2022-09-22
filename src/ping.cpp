#include "ping.h"
#include <tuple>
#include "assert.h"

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

    if (_exitCode == 0) {
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
    if (_exitCode == 0 || _exitCode == 256) {
        _time = getTime();
        _packetLoss = getPacketLoss();
    }
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

float Ping::packetLoss() {
    return _packetLoss;
}

int Ping::time() {
    return _time;
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

float Ping::getPacketLoss() {
    if (_exitCode == 2)
        return 0.0;

    int i = 0;
    const char startPattern[] = "received, ";
    const char endPattern[] = "% packet loss, time ";

    size_t start = _stdout.find(startPattern);
    size_t end = _stdout.find(endPattern);

    float loss = stof(_stdout.substr(start + sizeof(startPattern) - 1, end - start - sizeof(startPattern) + 1));

    return loss;
}

int Ping::getTime() {
    if (_exitCode == 2)
        return 0.0;

    const char startPattern[] = " packet loss, time ";
    const char endPattern[] = "ms";

    size_t start = _stdout.find(startPattern);
    size_t end = _stdout.find(endPattern);

    int time = stoi(_stdout.substr(start + sizeof(startPattern) - 1, end - start - sizeof(startPattern) + 1));

    return time;
}