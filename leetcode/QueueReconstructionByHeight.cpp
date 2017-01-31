// 406. Queue Reconstruction by Height
class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        vector<pair<int, int>> res;
        int n = people.size();
        if (n == 0) {
            return res;
        }
        int prev[n];
        for (int i = 0; i < n; ++i) {
            prev[i] = people[i].second;
        }
        for (int t = 0; t < n; ++t) {
            int min_val = INT_MAX;
            int min_id = 0;
            for (int i = 0; i < n; ++i) {
                if (prev[i] == 0 && people[i].first < min_val) {
                    min_val = people[i].first;
                    min_id = i;
                }
            }
            prev[min_id] = -1;
            res.push_back(people[min_id]);
            for (int i = 0; i < n; ++i) {
                if (prev[i] > 0 && people[i].first <= min_val) {
                    prev[i]--;
                }
            }
        }
        return res;
    }
};
