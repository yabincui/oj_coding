class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int cur = -1;
        for (int i = 0; i < bits.size(); ++i) {
            if (bits[i] == 0) {
                cur = 0;
            } else {
                cur = 1;
                i++;
            }
        }
        return cur == 0;
    }
};