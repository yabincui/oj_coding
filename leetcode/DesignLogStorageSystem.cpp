class LogSystem {
    
    struct Log {
        /*
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        */
        int date[6];
        int id;
        Log() {
            memset(date, 0, sizeof(date));
            id = 0;
        }
        
        Log(const string& timestamp) {
            memset(date, 0, sizeof(date));
            const char* p = timestamp.c_str();
            int i = 0;
            while (*p != '\0') {
                if (isdigit(*p)) {
                    date[i] = date[i] * 10 + *p - '0';
                } else if (*p == ':') {
                    i++;
                }
                p++;
            }
            id = 0;
        }
    };

    int compareLog(Log& log1, Log& log2, int cmp_level) {
        for (int i = 0; i < 6; ++i) {
            if (log1.date[i] != log2.date[i]) {
                return log1.date[i] > log2.date[i] ? 1 : -1;
            }
            if (i == cmp_level) {
                return 0;
            }
        }
        return 0;
    }
    
    int getCmpLevel(const string& gra) {
        for (int i = 0; i < gras.size(); ++i) {
            if (gra == gras[i]) {
                return i;
            }
        }
        return -1;
    }
    vector<string> gras;
    vector<Log> logs;
    
public:
    LogSystem() {
        gras.push_back("Year");
        gras.push_back("Month");
        gras.push_back("Day");
        gras.push_back("Hour");
        gras.push_back("Minute");
        gras.push_back("Second");
    }
    
    void put(int id, string timestamp) {
        logs.push_back(Log(timestamp));
        logs.back().id = id;
    }
    
    vector<int> retrieve(string s, string e, string gra) {
        Log begin(s);
        Log end(e);
        int cmp_level = getCmpLevel(gra);
        vector<int> res;
        for (auto& log : logs) {
            if (compareLog(begin, log, cmp_level) <= 0 && compareLog(log, end, cmp_level) <= 0) {
                res.push_back(log.id);
            }
        }
        return res;
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem obj = new LogSystem();
 * obj.put(id,timestamp);
 * vector<int> param_2 = obj.retrieve(s,e,gra);
 */
