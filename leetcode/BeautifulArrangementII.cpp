class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<int> result;
        if (k == n) return result;
        for (int i = 1; i < n - k; ++i) {
            result.push_back(i);
        }
        int left = n - k;
        int right = n;
        while (left <= right) {
            result.push_back(left++);
            if (left <= right) {
                result.push_back(right--);
            }
        }
        return result;
    }
};
