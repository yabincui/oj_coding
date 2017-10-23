class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if (nums.empty()) return vector<int>();
        sort(nums.begin(), nums.end());
        vector<pair<int, int>> v(nums.size(), make_pair(0, 0));
        for (int i = 1; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] % nums[j] == 0) {
                    if (v[i].first < v[j].first + 1) {
                        v[i].first = v[j].first + 1;
                        v[i].second = j;
                    }
                }
            }
        }
        int max_pos = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (v[i].first > v[max_pos].first) {
                max_pos = i;
            }
        }
        int count = v[max_pos].first;
        vector<int> res(count + 1);
        int cur = max_pos;
        res[count] = nums[cur];
        while (count--) {
            cur = v[cur].second;
            res[count] = nums[cur];
        }
        return res;
    }
};