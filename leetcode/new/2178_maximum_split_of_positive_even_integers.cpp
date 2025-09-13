// key: greedy
// error: high limit is wrong.
class Solution {
public:
    vector<long long> maximumEvenSplit(long long finalSum) {
        if (finalSum % 2 == 1 || finalSum < 1) {
            return {};
        }
        finalSum /= 2;
        long long low = 0;
        long long high = (long long)sqrt(finalSum * 2) + 1;
        while (low + 1 < high) {
            long long n = (low + high) / 2;
            if (n * (n + 1) / 2 + n < finalSum) {
                low = n;
            } else {
                high = n - 1;
            }
        }
        if (high == low + 1) {
            if (high * (high + 1) / 2 + high < finalSum) {
                low = high;
            }
        }
        long long rest = finalSum - low * (low + 1) / 2;
        vector<long long> result;
        for (long long i = 1; i <= low; i++) {
            result.push_back(i * 2);
        }
        result.push_back(rest * 2);
        return result;
    }
};