#include <iostream>
#include "ping.h"
#include "cfgfile.h"
#include <chrono>
#include "database.h"

using namespace std;

int main() {
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;

    map<string, string> cfg;
    readConfigFile(cfg);
    const string flags = "-q -c " + cfg["PING_COUNT"] + " -w " + cfg["TIMEOUT"];
    vector<string> hosts = parseHosts(cfg["HOSTS"]);

    Database db = Database("hostupd.db");

    for(string host : hosts) {
        string sql = "CREATE TABLE IF NOT EXISTS \"" + host +
                "\" (\n"
                "\t\"min\"\tNUMERIC,\n"
                "\t\"avg\"\tNUMERIC,\n"
                "\t\"max\"\tNUMERIC,\n"
                "\t\"packet_loss\"\tNUMERIC,\n"
                "\t\"time\"\tINTEGER,\n"
                "\t\"date\"\tINTEGER,\n"
                "\tPRIMARY KEY(\"date\")\n"
                ");";
        db.exec(sql);
    }

    while (true) {
        for(string host : hosts) {
            Ping p = Ping(host, flags, cfg["PING_PATH"]);
            string sql = "INSERT INTO \"" + host + "\" (min, avg, max, packet_loss, time, date) " +
                    "VALUES (" + to_string(p.min()) + "," + to_string(p.avg()) + "," + to_string(p.max()) + ","
                    + to_string(p.packetLoss()) + "," + to_string(p.time()) + "," + to_string(std::time(nullptr)) + ");";
            //cout << sql << endl;
            db.exec(sql);
        }

        sleep_until(system_clock::now() + std::chrono::seconds(getSeconds(cfg["INTERVAL"])));
    }

    return 0;
}
