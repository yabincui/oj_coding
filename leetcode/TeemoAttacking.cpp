class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int sum = 0;
        int prev = -1;
        for (auto t : timeSeries) {
            if (prev != -1) {
                sum += min(t - prev, duration);
            }
            prev = t;
        }
        if (prev != -1) {
            sum += duration;
        }
        return sum;
    }
};
