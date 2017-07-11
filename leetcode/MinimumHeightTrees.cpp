class Solution {
    
    // longest path, the middle one, or the middle two.
    // what if we have multiple longest paths. if they have interact, it must be middle, otherwise get a longer one.
    // if they don't interact, it is impossible.
    // so find the longest path.
    
    struct Node {
        int len;
        int from;
        int to;
    };
    
    struct Depth {
        int len;
        int from;
        Depth(int len, int from) : len(len), from(from) {}
    };
    
    Depth dfs(int root, int from, vector<vector<int>>& neighbors, Node* maxNode) {
        Depth ret(0, root);
        
        for (int next : neighbors[root]) {
            if (next == from) continue;
            Depth depth = dfs(next, root, neighbors, maxNode);
            int len = ret.len + depth.len + 1;
            if (len > maxNode->len) {
                maxNode->len = len;
                maxNode->from = ret.from;
                maxNode->to = depth.from;
            }
            if (ret.len < depth.len) {
                ret.len = depth.len;
                ret.from = depth.from;
            }
        }
        ret.len++;
        return ret;
    }
    
    bool findMiddle(int cur, int pos, int parent, vector<vector<int>>& neighbors, Node& maxNode, vector<int>& middle_points) {
        bool need_pos = false;
        if (maxNode.len % 2 == 0) {
            need_pos = (pos == maxNode.len / 2 - 1 || pos == maxNode.len / 2);
        } else {
            need_pos = (pos == maxNode.len / 2);
        }
        
        if (cur == maxNode.to) {
            if (need_pos) {
                middle_points.push_back(cur);
            }
            return true;
        }
        for (int next : neighbors[cur]) {
            if (next == parent) continue;
            if (findMiddle(next, pos + 1, cur, neighbors, maxNode, middle_points)) {
                if (need_pos) middle_points.push_back(cur);
                return true;
            }
        }
        return false;
    }
    
public:
    
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if (n == 1) {
            return {0};
        }
        vector<vector<int>> neighbors(n);
        for (auto& pair : edges) {
            neighbors[pair.first].push_back(pair.second);
            neighbors[pair.second].push_back(pair.first);
        }
        // 1. find the longest path in the graph.
        Node maxNode;
        maxNode.len = 0;
        dfs(0, -1, neighbors, &maxNode);
        
        // 2. find the middle points in the longest path.
        // if len == 2, find len/2 len/2 - 1
        // if len == 3, find len/2.
        //printf("maxNode, len = %d, from %d, to %d\n", maxNode.len, maxNode.from, maxNode.to);
        vector<int> middle_points;
        findMiddle(maxNode.from, 0, -1, neighbors, maxNode, middle_points);
        
        
        bool visited[n];
        int minDepth = INT_MAX;
        vector<int> res;
        for (int root : middle_points) {
            //printf("middle_points %d\n", root);
            memset(visited, 0, sizeof(visited));
            visited[root] = true;
            queue<int> q;
            q.push(root);
            int depth = 0;
            while (!q.empty()) {
                int size = q.size();
                for (int i = 0; i < size; ++i) {
                    int cur = q.front(); q.pop();
                    for (auto& neighbor : neighbors[cur]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
                depth++;
            }
            if (minDepth > depth) {
                minDepth = depth;
                res.clear();
                res.push_back(root);
            } else if (minDepth == depth) {
                res.push_back(root);
            }
        }
        return res;
    }
    
    vector<int> findMinHeightTreesON2(int n, vector<pair<int, int>>& edges) {
        if (n == 1) {
            return {0};
        } else if (n == 2) {
            return {0, 1};
        }
        vector<vector<int>> neighbors(n);
        for (auto& pair : edges) {
            neighbors[pair.first].push_back(pair.second);
            neighbors[pair.second].push_back(pair.first);
        }
        bool visited[n];
        int minDepth = INT_MAX;
        vector<int> res;
        for (int root = 0; root < n; ++root) {
            if (neighbors[root].size() == 1) continue;
            memset(visited, 0, sizeof(visited));
            visited[root] = true;
            queue<int> q;
            q.push(root);
            int depth = 0;
            while (!q.empty()) {
                int size = q.size();
                for (int i = 0; i < size; ++i) {
                    int cur = q.front(); q.pop();
                    for (auto& neighbor : neighbors[cur]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
                depth++;
            }
            if (minDepth > depth) {
                minDepth = depth;
                res.clear();
                res.push_back(root);
            } else if (minDepth == depth) {
                res.push_back(root);
            }
        }
        return res;
    }
};
