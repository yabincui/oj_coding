class Solution {
    
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    
    int recur(vector<vector<int>>& grid, int r, int c) {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) {
            return 0;
        }
        if (grid[r][c] == 0) {
            return 0;
        }
        int result = 1;
        grid[r][c] = 0;
        for (int d = 0; d < 4; ++d) {
            result += recur(grid, r + dr[d], c + dc[d]);
        }
        return result;
    }
    
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }
        int result = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j]) {
                    int count = recur(grid, i, j);
                    result = max(result, count);
                }
            }
        }
        return result;
    }
};
