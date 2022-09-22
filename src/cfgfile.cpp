#include "cfgfile.h"

void readConfigFile(map<string,string> &cfg) {
    ifstream cfgFile("hostupd.conf");
    assert(cfgFile.is_open());
    string line;
    while (getline(cfgFile, line)) {
        int delim = line.find("=");
        string key = line.substr(0, delim);
        //cout << key << endl;
        string value = line.substr(delim + 1, line.length());
        //cout << value << endl;
        cfg.insert(pair<string, string>(key, value));
    }
    cfgFile.close();
}

int getSeconds(string s) {
    switch (char(s.back())) {
        case 's': {
            return stoi(s.erase(s.length() - 1, 1));
        }
        case 'm': {
            return stoi(s.erase(s.length() - 1, 1)) * 60;
        }
        case 'h': {
            return stoi(s.erase(s.length() - 1, 1)) * 3600;
        }
    }
}

vector<string> parseHosts(const string &s) {
    vector<string> res;
    string host;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] != ' ' && s[i] != ',') {
            host += s[i];
        } if (s[i] == ',' && !host.empty()) {
            res.push_back(host);
            host = "";
        }
    }
    if (!host.empty())
        res.push_back(host);
    return res;
}
