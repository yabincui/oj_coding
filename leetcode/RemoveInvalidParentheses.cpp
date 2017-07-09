class Solution {
    
    void addCharToSet(unordered_set<string>& origin, char c, unordered_set<string>& dest) {
        string tmp;
        tmp.push_back(c);
        for (auto& s : origin) {
            dest.insert(s + tmp);
        }
    }
    
    void addSet(unordered_set<string>& from, unordered_set<string>& dest) {
        dest.insert(from.begin(), from.end());
    }
    
public:
    vector<string> removeInvalidParentheses(string s) {
        int n = s.size();
        vector<int> needLeftParenPrefix(n + 1, 0);
        int rparen_count = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == '(') {
                if (rparen_count > 0) {
                    rparen_count--;
                }
                needLeftParenPrefix[i] = max(0, needLeftParenPrefix[i+1] - 1);
            } else if (s[i] == ')') {
                rparen_count++;
                needLeftParenPrefix[i] = needLeftParenPrefix[i+1] + 1;
            } else {
                needLeftParenPrefix[i] = needLeftParenPrefix[i+1];
            }
        }
        
        // To remove minimal count, you'd better keep >= needLeftParenPrefix[i] left parens.
        // lparen -> strings in this lparen state.
        unordered_map<int, unordered_set<string>> ps[2], *cur, *next;
        cur = &ps[0];
        next = &ps[1];
        
        (*cur)[0].insert("");
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            next->clear();
            
            if (c == '(') {
                // 1. For lparen < needLeftParenPrefix[i+1], must add it.
                // 2. For lparen >= needLeftParenPrefix[i+1], add it or not.
                
                for (auto& pair : *cur) {
                    // 1. add it.
                    addCharToSet(pair.second, c, (*next)[pair.first + 1]);
                    if (pair.first >= needLeftParenPrefix[i+1]) {
                        addSet(pair.second, (*next)[pair.first]);
                    }
                }
            } else if (c == ')') {
                // 1. For lparen > 0, add it.
                // 2. For lparen <= needLeftParenPrefix[i+1], skip it.
                for (auto& pair : *cur) {
                    if (pair.first > 0) {
                        addCharToSet(pair.second, c, (*next)[pair.first - 1]);
                    }
                    if (pair.first <= needLeftParenPrefix[i+1]) {
                        addSet(pair.second, (*next)[pair.first]);
                    }
                }
            } else {
                // Add it.
                for (auto& pair : *cur) {
                    addCharToSet(pair.second, c, (*next)[pair.first]);
                }
            }
            
            swap(cur, next);
        }
        
        vector<string> res((*cur)[0].begin(), (*cur)[0].end());
        return res;
    }
};
