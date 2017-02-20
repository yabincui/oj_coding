// 520. Detect Capital
class Solution {
public:
    bool detectCapitalUse(string word) {
        int up_count = 0;
        int low_count = 0;
        for (int i = 0; i < word.size(); ++i) {
            if (isupper(word[i])) {
                up_count++;
            } else {
                low_count++;
            }
        }
        if (up_count == word.size()) {
            return true;
        }
        if (low_count == word.size()) {
            return true;
        }
        if (up_count == 1 && isupper(word[0]) && word.size() > 1) {
            return true;
        }
        return false;
    }
};
