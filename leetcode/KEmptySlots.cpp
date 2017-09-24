class Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        // map of blooming flowers sort by position.
        set<int> posSet;
        for (int i = 0; i < flowers.size(); ++i) {
            int curPos = flowers[i];
            auto it = posSet.insert(curPos).first;
            if (it != posSet.begin()) {
                auto it2 = it;
                it2--;
                if (curPos - *it2 - 1 == k) {
                    return i + 1;
                }
            }
            ++it;
            if (it != posSet.end()) {
                if (*it - curPos - 1 == k) {
                    return i + 1;
                }
            }
        }
        return -1;
    }
};