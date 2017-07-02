class Solution {
public:
    int findDerangement(int n) {
        int i = 1;
        int64_t prevComplete = 0;
        int64_t prevMixOne = 1;
        int64_t curComplete = 0;
        int64_t curMixOne = 0;
        for (i = 2; i <= n; ++i) {
            curComplete = (i - 1) * prevMixOne;
            curMixOne = prevComplete + (i - 1) * prevMixOne;
        
            prevComplete = curComplete % 1000000007;
            prevMixOne = curMixOne % 1000000007;
        }
        return (int)prevComplete;
    }
};
