class Solution {
    
    typedef vector<pair<int, int>> Node;
    
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    
    int recur(vector<vector<int>>& grid, int r, int c, Node& node) {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) {
            return 0;
        }
        if (grid[r][c] == 0) {
            return 0;
        }
        int result = 1;
        grid[r][c] = 0;
        node.push_back(make_pair(r, c));
        for (int d = 0; d < 4; ++d) {
            result += recur(grid, r + dr[d], c + dc[d], node);
        }
        return result;
    }
    
    void uniform(Node& node) {
        sort(node.begin(), node.end());
        int r = node[0].first;
        int c = node[0].second;
        for (auto& n : node) {
            n.first -= r;
            n.second -= c;
        }
    }
    
    static size_t hash(const Node& node) {
        return node.size();
    }
    
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }
        
        unordered_set<Node, decltype(&hash)> hit_set(1000, hash);
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j]) {
                    Node node;
                    recur(grid, i, j, node);
                    uniform(node);
                    hit_set.insert(node);
                }
            }
        }
        return hit_set.size();
    }
};


