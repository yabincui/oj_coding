class Solution {
    
    void recur(const char*& s, map<string, int>& count_map) {
        while (true) {
            if (*s == ')' || *s == '\0') {
                return;
            }
            if (*s == '(') {
                map<string, int> inner_map;
                s++;
                recur(s, inner_map);
                s++; // ')'
                // read a count
                int repeat = 0;
                while (isdigit(*s)) {
                    repeat = repeat * 10 + *s - '0';
                    s++;
                }
                if (repeat == 0) {
                    repeat = 1;
                }
                for (auto& pair : inner_map) {
                    count_map[pair.first] += pair.second * repeat;
                }
            } else {
                string key;
                if (isupper(*s)) {
                    key.push_back(*s++);
                    while (islower(*s)) {
                        key.push_back(*s++);
                    }
                    // read a count
                    int repeat = 0;
                    while (isdigit(*s)) {
                        repeat = repeat * 10 + *s - '0';
                        s++;
                    }
                    if (repeat == 0) {
                        repeat = 1;
                    }
                    count_map[key] += repeat;
                }
            }
        }
    }
    
public:
    string countOfAtoms(string formula) {
        std::map<string, int> count_map;
        const char* s = formula.c_str();
        recur(s, count_map);
        string res;
        for (auto& pair : count_map) {
            res += pair.first;
            if (pair.second > 1) {
                res += to_string(pair.second);
            }
        }
        return res;
    }
};
