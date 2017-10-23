class Solution {
    
    bool isvowel(char c) {
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
    
public:
    string reverseVowels(string s) {
        vector<int> pos_v;
        vector<char> char_v;
        for (int i = 0; i < s.size(); ++i) {
            if (isvowel(s[i])) {
                pos_v.push_back(i);
                char_v.push_back(s[i]);
            }
        }
        for (int i = 0; i < pos_v.size(); ++i) {
            s[pos_v[i]] = char_v[char_v.size() - 1 - i];
        }
        return s;
    }
};