class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> prev_count(numCourses, 0);
        vector<vector<int>> next(numCourses);
        for (auto& pair : prerequisites) {
            next[pair.second].push_back(pair.first);
            prev_count[pair.first]++;
        }
        vector<int> res;
        queue<int> zero_q;
        for (int i = 0; i < numCourses; ++i) {
            if (prev_count[i] == 0) {
                zero_q.push(i);
            }
        }
        while (!zero_q.empty()) {
            int cur = zero_q.front(); zero_q.pop();
            res.push_back(cur);
            for (auto i : next[cur]) {
                if (--prev_count[i] == 0) {
                    zero_q.push(i);
                }
            }
        }
        if (res.size() < numCourses) {
            res.clear();
        }
        return res;
    }
};
