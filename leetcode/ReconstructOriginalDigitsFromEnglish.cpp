// 423. Reconstruct Original Digits from English
class Solution {
public:
    char* digit_str[10] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };

    string originalDigits(string s) {
        int ch_count[26];
        memset(ch_count, 0, sizeof(ch_count));
        for (auto& c : s) {
            ch_count[c - 'a']++;
        }
        int digit_count[10];
        memset(digit_count, 0, sizeof(digit_count));
        bool used[10];
        memset(used, 0, sizeof(used));
        for (int i = 0; i < 10; ++i) {
            int d = getSingleDigit(used);
            used[d] = true;
            int count = consumeDigit(ch_count, d);
            //printf("getSingleDigit = %d, consumeDigit = %d\n", d, count);
            digit_count[d] = count;
        }
        string res;
        for (int i = 0; i < 10; ++i) {
            char c = i + '0';
            for (int j = 0; j < digit_count[i]; ++j) {
                res.push_back(c);
            }
        }
        return res;
    }
    
    int getSingleDigit(bool used[10]) {
        int mark[26];
        memset(mark, -1, sizeof(mark));
        for (int i = 0; i < 10; ++i) {
            if (!used[i]) {
                char* t = digit_str[i];
                for (int j = 0; t[j] != '\0'; ++j) {
                    if (mark[t[j]-'a'] == -1 || mark[t[j]-'a'] == i) {
                        mark[t[j]-'a'] = i;
                    } else {
                        mark[t[j]-'a'] = -2;
                    }
                }
            }
        }
        for (int i = 0; i < 26; ++i) {
            if (mark[i] >= 0) {
                return mark[i];
            }
        }
        return -1;
    }
    
    int consumeDigit(int ch_count[26], int d) {
        int need[26];
        for (int i = 0; i < 26; ++i) {
            need[i] = 0;
            char* t = digit_str[d];
            for (int j = 0; t[j] != '\0'; ++j) {
                if (t[j] == i + 'a') {
                    need[i]++;
                }
            }
        }
        int count = INT_MAX;
        for (int i = 0; i < 26; ++i) {
            if (need[i] == 0) {
                continue;
            }
            //printf("[%d] need %d %c, has %d, count = %d\n", d, need[i], i + 'a', ch_count[i], ch_count[i] / need[i]);
            count = min(ch_count[i] / need[i], count);
        }
        //printf("has digit %d, %d times\n", d, count);
        for (int i = 0; i < 26; ++i) {
            ch_count[i] -= need[i] * count;
        }
        return count;
    }
    
    
};
