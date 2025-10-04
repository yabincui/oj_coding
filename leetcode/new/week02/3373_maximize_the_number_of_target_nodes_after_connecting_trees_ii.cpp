// key: tree traversal
// no error
class Solution {
   public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        // node 0 (3 even, 5 odd)
        // node 1 (5 even, 3 odd)
        // node 2 (5 even, 3 odd)
        // node 3 (5 even, 3 odd)
        // node 4 (3 even, 5 odd)
        // calculate self tree.
        // calculate neighbor tree.
        // use 1 BFS to calculate dist to one node.
        // then assign dist to all other nodes.
        vector<int> even1 = getTreeEvenCount(edges1);
        vector<int> even2 = getTreeEvenCount(edges2);
        int tree2_size = edges2.size() + 1;
        int add = max(even2[0], tree2_size - even2[0]);
        for (auto& even : even1) {
            even += add;
        }
        return even1;
    }

    vector<int> getTreeEvenCount(const vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> neighbor(n);
        for (const auto& e : edges) {
            neighbor[e[0]].push_back(e[1]);
            neighbor[e[1]].push_back(e[0]);
        }
        vector<int> dist(n, -1);
        dist[0] = 0;
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int n : neighbor[cur]) {
                if (dist[n] == -1) {
                    dist[n] = dist[cur] + 1;
                    q.push(n);
                }
            }
        }
        vector<int> result(n);
        for (int d : dist) {
            if (d % 2 == 0) {
                result[0]++;
            }
        }
        for (int i = 1; i < n; i++) {
            if (dist[i] % 2 == 0) {
                result[i] = result[0];
            } else {
                result[i] = n - result[0];
            }
        }
        return result;
    }
};