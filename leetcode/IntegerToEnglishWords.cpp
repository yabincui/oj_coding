// 273. Integer to English Words
class Solution {
public:
    const char* s[20] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
    };
    const char* s10[10] = {
        "zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };
    const char* s100[2] = {
        "zero", "hundred",
    };
    const char* s1000[4] = {
        "zero", "thousand", "million", "billion",
    };
    
    void addWord(string& s, const char* t) {
        s.push_back(toupper(*t++));
        while (*t != '\0') {
            s.push_back(*t++);
        }
    }
    
    string toWordIn1000(int num) {
      string res;
      if (num / 100 > 0) {
          addWord(res, s[num / 100]);
          res += " ";
          addWord(res, s100[1]);
          num %= 100;
      }
      if (num == 0) {
          // pass
      } else if (num < 20) {
          if (!res.empty()) res += " ";
          addWord(res, s[num]);
      } else {
          if (!res.empty()) res += " ";
          addWord(res, s10[num / 10]);
          num %= 10;
          if (num != 0) {
              res += " ";
              addWord(res, s[num]);
          }
      }
      return res;
    }

    string numberToWords(int num) {
        string res;
        if (num == 0) {
            addWord(res, s[0]);
            return res;
        }
        for (int i = 1000000000, j= 3; i >= 1; i /= 1000, j--) {
            string tmp = toWordIn1000(num / i % 1000);
            num %= i;
            if (!tmp.empty()) {
                if (j != 0) {
                    tmp += " ";
                    addWord(tmp, s1000[j]);
                }
                if (!res.empty()) {
                    res += " ";
                }
                res += tmp;
            }
        }
        return res;
    }
};
