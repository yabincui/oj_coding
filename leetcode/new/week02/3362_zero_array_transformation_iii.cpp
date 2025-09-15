// key: sort, unordered_map, map.rbegin()
// error: didn't consider negative value when adding to result.
// error: didn't consider result is to_fixed, or to_remove.
class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        // query, [l, r], sort by l
        // is there any greedy?
        // if accumulate sum, if acc_sum[i] >= nums[i], can kill.
        // can we always remove the query having the smallest r? The least useful one.
        // use unordered_map to find queries hit by a location. add it to a map with key: r.
        // need to a way to mark a query is fixed to have. At last, see how many queries are fixed.

        // if want to fix, find the one with the largest r value to fix.
        unordered_map<int, int> add_query_map;
        unordered_map<int, int> remove_query_map;
        unordered_set<int> fixed_queries;
        int fixed_queries_in_use = 0;
        // map from r, to how many fixed queries ends with r - 1 (excluding r).
        map<int, int> fixed_query_map;
        // map from r, to how many queries ends with r - 1 (excluding r).
        map<int, int> dynamic_query_map;
        int dynamic_queries_in_use = 0;

        sort(queries.begin(), queries.end());
        int new_query_id = 0;
        int total_fixed = 0;

        for (int i = 0; i < nums.size(); i++) {
            // 1. exclude queries ends at i.
            if (auto it = fixed_query_map.find(i); it != fixed_query_map.end()) {
                fixed_queries_in_use -= it->second;
                fixed_query_map.erase(it);
            }
            if (auto it = dynamic_query_map.find(i); it != dynamic_query_map.end()) {
                dynamic_queries_in_use -= it->second;
                dynamic_query_map.erase(it);
            }
            // 2. add queries starts at i.
            while (new_query_id < queries.size() && queries[new_query_id][0] == i) {
                int exclude_r = queries[new_query_id][1] + 1;
                dynamic_queries_in_use++;
                dynamic_query_map[exclude_r]++;
                new_query_id++;
            }
            // 3. check if query count is enough.
            if (nums[i] > fixed_queries_in_use + dynamic_queries_in_use) {
                return -1;
            }
            // 4. fix queries.
            int to_fix = nums[i] - fixed_queries_in_use;
            printf("i = %d, to_fix=%d\n", i, to_fix);
            while (to_fix > 0) {
                auto it = dynamic_query_map.rbegin();
                int exclude_r = it->first;
                int k = min(to_fix, it->second);
                it->second -= k;
                if (it->second == 0) {
                    dynamic_query_map.erase(exclude_r);
                }
                dynamic_queries_in_use -= k;
                fixed_queries_in_use += k;
                fixed_query_map[exclude_r] += k;
                to_fix -= k;
                total_fixed += k;
            }
        }
        return queries.size() - total_fixed;
    }
};

