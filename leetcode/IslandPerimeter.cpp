class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int res = 0;
        int rows = grid.size();
        if (rows == 0) return 0;
        int cols = grid[0].size();
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 0) continue;
                for (int i = 0; i < 4; ++i) {
                    int tr = r + dr[i];
                    int tc = c + dc[i];
                    if (tr >= 0 && tr < rows && tc >= 0 && tc < cols && grid[tr][tc]) {
                        continue;
                    }
                    res++;
                }
            }
        }
        return res;
    }
};
