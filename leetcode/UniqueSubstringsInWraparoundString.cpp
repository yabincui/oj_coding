class Solution {
    
    char get_next(char c) {
        return c == 'z' ? 'a' : c + 1;
    }
    
    void update_length(vector<int>& length, char start, int len) {
        char c = start;
        do {
            length[c - 'a'] = max(length[c - 'a'], len);
            c = get_next(c);
            len--;
        } while (len > 0 and c != start);
    }
    
public:
    int findSubstringInWraproundString(string p) {
        if (p.empty()) return 0;
        vector<int> length(26);
        char cur = p[0];
        char start = p[0];
        int len = 1;
        for (int i = 1; i < p.size(); ++i) {
            if (p[i] == get_next(cur)) {
                len++;
            } else {
                update_length(length, start, len);
                len = 1;
                start = p[i];
            }
            cur = p[i];
        }
        update_length(length, start, len);
        int result = 0;
        for (auto v : length) {
            result += v;
        }
        return result;
    }
};
