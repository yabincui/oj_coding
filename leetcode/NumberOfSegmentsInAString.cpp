class Solution {
public:
    int countSegments(string s) {
        int count = 0;
        bool space = true;
        for (char c : s) {
            if (!isspace(c)) {
                if (space) {
                    space = false;
                    count++;
                }
            } else {
                space = true;
            }
        }
        return count;
    }
};