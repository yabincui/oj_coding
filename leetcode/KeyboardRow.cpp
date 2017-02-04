// 500. Keyboard Row
class Solution {
public:
    const char* s[3] = {
        "QWERTYUIOP",
        "ASDFGHJKL",
        "ZXCVBNM",
    };
    vector<string> findWords(vector<string>& words) {
      int word[26];
      for (int i = 0; i < 3; ++i) {
          for (int j = 0; s[i][j] != '\0'; ++j) {
              word[s[i][j]-'A'] = i;
          }
      }
      vector<string> res;
      for (auto& s : words) {
          if (s.empty()) {
              res.push_back(s);
              continue;
          }
          int r = word[toupper(s[0]) - 'A'];
          bool valid = true;
          for (int i = 1; i < s.size(); ++i) {
              if (r != word[toupper(s[i]) - 'A']) {
                  valid = false;
                  break;
              }
          }
          if (valid) {
              res.push_back(s);
          }
      }
      return res;
    }
};
