class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if (numCourses <= 0) return true;
        vector<int> prev(numCourses, 0);
        vector<vector<int>> after(numCourses);
        for (auto& pair : prerequisites) {
            prev[pair.first]++;
            after[pair.second].push_back(pair.first);
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (prev[i] == 0) {
                q.push(i);
            }
        }
       int visitCount = 0;
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            visitCount++;
            for (auto t : after[cur]) {
                prev[t]--;
                if (prev[t] == 0) {
                    q.push(t);
                }
            }
        }
        return visitCount == numCourses;
    }
};
