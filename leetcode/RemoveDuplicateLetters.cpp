class Solution {
public:

    string removeDuplicateLetters(string s) {
        unordered_map<char, int> hit_map;
        for (auto& c : s) {
            hit_map[c]++;
        }
        string cur_stack;
        int cur_bitmask = 0;
        for (auto& c : s) {
            // whether we want to push c to stack.
            int bit = 1 << (c - 'a');
            hit_map[c]--;
            if (cur_bitmask & bit) {
                continue;
            }
            while (!cur_stack.empty() && cur_stack.back() > c && hit_map[cur_stack.back()] > 0) {
                cur_bitmask &= ~(1 << (cur_stack.back() - 'a'));
                cur_stack.pop_back();
            }
            cur_stack.push_back(c);
            cur_bitmask |= bit;
        }
        return cur_stack;
    }

    string removeDuplicateLettersTimeout(string s) {
        if (s.empty()) return s;
        unordered_set<char> hit_set;
        vector<bool> is_last(s.size(), false);
        for (int i = s.size() - 1; i >= 0; --i) {
            if (hit_set.find(s[i]) == hit_set.end()) {
                is_last[i] = true;
                hit_set.insert(s[i]);
            }
        }
        unordered_map<int, string> map[2];
        unordered_map<int, string>* cur_map = &map[0];
        unordered_map<int, string>* next_map = &map[1];
        (*cur_map)[0] = "";
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            int bit = 1 << (c - 'a');
            next_map->clear();
            for (auto& pair : *cur_map) {
                if (pair.first & bit) {
                    addValue(next_map, pair.first, pair.second);
                } else {
                    addValue(next_map, pair.first | bit, pair.second + c);
                    if (!is_last[i]) {
                        addValue(next_map, pair.first, pair.second);
                    }
                }
            }
            swap(cur_map, next_map);
        }
        return (cur_map->begin()->second);
    }
    
    void addValue(unordered_map<int, string>* map, int mask, const string& value) {
        auto it = map->find(mask);
        if (it == map->end() || it->second > value) {
            (*map)[mask] = value;
        }
    }
};
