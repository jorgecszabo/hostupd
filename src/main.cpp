#include <iostream>
#include "ping.h"

using namespace std;

int main() {
    Ping a = Ping("192.168.0.1", "-q -c 5", "/usr/bin/ping");
    cout << a.avg() << endl;
    cout << a.exitCode() << endl;

    Ping b = Ping("192.168.0.100", "-q -c 5", "/usr/bin/ping");
    cout << b.max() << endl;

    return 0;
}
