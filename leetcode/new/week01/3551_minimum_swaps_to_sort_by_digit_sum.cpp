// key: array sort
// no error
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        vector<tuple<int, int, int>> v;
        for (int i = 0; i < nums.size(); i++) {
            int value = nums[i];
            int sum = 0;
            while (value != 0) {
                sum += value % 10;
                value /= 10;
            }
            v.push_back({sum, nums[i], i});
        }
        sort(v.begin(), v.end());
        int result = 0;
        for (int i = 0; i < v.size(); i++) {
            int order = get<2>(v[i]);
            while (order != i) {
                result++;
                int j = get<2>(v[order]);
                get<2>(v[order]) = order;
                order = j;
            }
        }
        return result;
    }
};