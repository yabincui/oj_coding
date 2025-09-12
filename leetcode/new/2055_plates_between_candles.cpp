// key: array, accumulate sum, upper_lower_bound
// error: wrong parameter to upper_bound.
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> acc_candle(n, 0);
        if (n > 0) {
            acc_candle[0] = s[0] == '|' ? 1 : 0;
        }
        for (int i = 1; i < n; i++) {
            acc_candle[i] = acc_candle[i - 1] + (s[i] == '|' ? 1 : 0);
        }
        vector<int> result;
        for (auto& q : queries) {
            int left = q[0];
            int right = q[1];
            int left_candle = acc_candle[left];
            int right_candle = acc_candle[right];
            if (left_candle == right_candle) {
                result.push_back(0);
                continue;
            }
            //printf("before left=%d, right=%d, left_candle=%d, right_candle=%d\n", left, right, left_candle, right_candle);

            // find left_candle.
            if (s[left] == '*') {
                auto it = upper_bound(acc_candle.begin() + left, acc_candle.begin() + right + 1, left_candle);
                left = it - acc_candle.begin();
                left_candle++;
            }
            // find right_candle.
            if (s[right] == '*') {
                auto it = lower_bound(acc_candle.begin() + left, acc_candle.begin() + right, right_candle);
                right = it - acc_candle.begin();
            }
            //printf("left=%d, right=%d, left_candle=%d, right_candle=%d\n", left, right, left_candle, right_candle);
            int length = right - left + 1;
            int candle_count = right_candle - left_candle + 1;
            result.push_back(length - candle_count);
        }
        return result;
    }
};