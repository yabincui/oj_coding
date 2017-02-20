// 420. Strong Password Checker
class Solution {
public:

    struct State {
        bool has_low;
        bool has_up;
        bool has_digit;
        bool repeated; // whether last_c has been repeated once.
        unsigned char last_c; // 0xff if a replaced one.
        unsigned char count;  // character count
    };
    
    void toState(int key, State& s) {
        s.has_low = key & 1;
        key >>= 1;
        s.has_up = key & 1;
        key >>= 1;
        s.has_digit = key & 1;
        key >>= 1;
        s.repeated = key & 1;
        key >>= 1;
        s.last_c = key & 0xff;
        key >>= 8;
        s.count = key & 0xff;
    }
    
    int toKey(State& s) {
        int res = 0;
        if (s.has_low) res |= 1;
        if (s.has_up) res |= 2;
        if (s.has_digit) res |= 4;
        if (s.repeated) res |= 8;
        res |= s.last_c << 4;
        res |= s.count << 12;
        return res;
    }
    
    void changeState(State& s, unsigned char c) {
        int j = 0;
        if (islower(c)) j = 0;
        else if (isupper(c)) j = 1;
        else if (isdigit(c)) j = 2;
        changeState(s, c, j);
    }
    
    void changeState(State& s, unsigned char c, int j) {
        if (j == 0) s.has_low = true;
        else if (j == 1) s.has_up = true;
        else if (j == 2) s.has_digit = true;
        if (s.count < 0xff) {
            s.count++;
        }
        if (c != 0xff && c == s.last_c) {
            if (s.repeated) {
                s.count = 0xff; // make it invalid;
            }
            s.repeated = true;
        } else {
            s.repeated = false;
        }
        s.last_c = c;
    }
    
    void addState(State& s, int value, map<int, int>* m) {
        if (s.count > 20) return;
        int key = toKey(s);
        auto it = m->find(key);
        if (it == m->end()) {
            (*m)[key] = value;
        } else {
            (*m)[key] = min(value, it->second);
        }
    }

    int strongPasswordChecker(string ts) {
        map<int, int> maps[2];
        map<int, int>* current = &maps[0];
        map<int, int>* next = &maps[1];
        State s, ns;
        s.has_low = false;
        s.has_up = false;
        s.has_digit = false;
        s.repeated = false;
        s.last_c = 0xff;
        s.count = 0;
        current->insert(make_pair(toKey(s), 0));
        for (int i = 0; i < ts.size(); ++i) {
            char c = ts[i];
            next->clear();
            for (auto& pair : *current) {
                toState(pair.first, s);
                // insert
                if (s.last_c == c && s.repeated) {
                    for (int j = 0; j < 3; ++j) {
                        ns = s;
                        changeState(ns, 0xff, j);
                        changeState(ns, c);
                        addState(ns, pair.second + 1, next);
                    }
                }
                // delete
                ns = s;
                addState(ns, pair.second + 1, next);
                
                // keep
                changeState(ns, c);
                addState(ns, pair.second, next);

                // change
                for (int j = 0; j < 3; ++j) {
                    ns = s;
                    changeState(ns, 0xff, j);
                    addState(ns, pair.second + 1, next);
                }
            }
            swap(current, next);
        }
        int res = INT_MAX;
        for (auto & pair : *current) {
            toState(pair.first, s);
            int need = max(6 - s.count, 0);
            int need2 = 0;
            if (!s.has_low) need2++;
            if (!s.has_up) need2++;
            if (!s.has_digit) need2++;
            need = max(need, need2) + pair.second;
            if (res > need) {
                res = need;
            }
        }
        return res;
    }
};
