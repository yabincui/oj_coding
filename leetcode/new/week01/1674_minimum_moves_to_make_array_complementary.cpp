// key: array, map
// error: didn't thought edge case, can use a sum that not hit by any numbers.
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        vector<int> sorted_a;
        vector<int> sorted_b;
        map<int, int> hit_map;
        int n = nums.size();
        int half_n = nums.size() / 2;
        for (int i = 0; i < half_n; i++) {
            int a = min(nums[i], nums[n - 1 - i]);
            int b = max(nums[i], nums[n - 1 - i]);
            sorted_a.push_back(a);
            sorted_b.push_back(b);
            hit_map[a + b]++;
        }
        sort(sorted_a.begin(), sorted_a.end());
        sort(sorted_b.begin(), sorted_b.end());

        int min_change = INT_MAX;
        int min_sum = hit_map.begin()->first;
        int max_sum = hit_map.rbegin()->first;
        for (int sum = min_sum; sum <= max_sum; sum++) {
            int count = 0;
            if (auto it = hit_map.find(sum); it != hit_map.end()) {
                count = it->second;
            }
            int need_change = half_n - count;
            // if b < sum - limit, need 2 changes.
            auto it = lower_bound(sorted_b.begin(), sorted_b.end(), sum - limit);
            need_change += it - sorted_b.begin();
            // if a >= sum, need 2 changes.
            it = lower_bound(sorted_a.begin(), sorted_a.end(), sum);
            if (it != sorted_a.end()) {
                need_change += sorted_a.end() - it;
            }
            min_change = min(min_change, need_change);
        }
        return min_change;
    }
};