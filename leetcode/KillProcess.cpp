class Solution {
    
    struct Node {
        vector<int> children; 
    };
    
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, Node> pid_map;
        for (int i = 0; i < pid.size(); ++i) {
            pid_map[ppid[i]].children.push_back(pid[i]);
        }
        vector<int> result;
        queue<int> q;
        q.push(kill);
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            result.push_back(cur);
            auto& s = pid_map[cur].children;
            for (int p : s) {
                q.push(p);
            }
        }
        return result;
    }
};