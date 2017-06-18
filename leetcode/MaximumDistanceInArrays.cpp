class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int m = arrays.size();
        vector<int> mins(m);
        vector<int> maxs(m);
        for (int i = 0; i < m; ++i) {
            mins[i] = maxs[i] = arrays[i][0];
            for (auto& v : arrays[i]) {
                mins[i] = min(mins[i], v);
                maxs[i] = max(maxs[i], v);
            }
        }
        map<int, int> max_map;
        for (auto& v : maxs) {
            max_map[v]++;
        }
        int max_diff = 0;
        for (int i = 0; i < m; ++i) {
            int a = mins[i];
            auto it = max_map.rbegin();
            int b = it->first;
            if (maxs[i] == b && it->second == 1) {
                b = (++it)->first;
            }
            int diff = abs(a - b);
            max_diff = max(max_diff, diff);
        }
        return max_diff;
    }
};
