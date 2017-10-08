class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        vector<int> nums;
        int64_t lastDiff;
        for (int i = 1; i < A.size(); ++i) {
            int64_t d = (int64_t)A[i] - A[i-1];
            if (i == 1) {
                lastDiff = d;
                nums.push_back(1);
            } else if (lastDiff == d) {
                nums.back()++;
            } else {
                nums.push_back(1);
                lastDiff = d;
            }
        }
        int sum = 0;
        for (auto n : nums) {
            if (n == 1) continue;
            n++;
            // i = 0..n-3   j=i+2..n-1 = (n-1-i-2+1) = n-i-2
            // ((n-2) + 1) * (n-2) / 2 = (n-1) * (n-2) / 2
            sum += (int64_t)(n -1) * (n-2) / 2;
        }
        return sum;
    }
};
