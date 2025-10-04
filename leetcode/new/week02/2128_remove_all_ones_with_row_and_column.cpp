// key: array
// no error
class Solution {
   public:
    bool removeOnes(vector<vector<int>>& grid) {
        // flip rows as needed by the first column.
        // then flip columns as needed. check if can be all zero.
        if (grid.empty() || grid[0].empty()) {
            return true;
        }
        int rows = grid.size();
        int cols = grid[0].size();
        vector<bool> flip_rows(rows, false);
        for (int r = 0; r < rows; r++) {
            if (grid[r][0] == 1) {
                flip_rows[r] = true;
            }
        }
        for (int c = 1; c < cols; c++) {
            int value = grid[0][c];
            if (flip_rows[0]) {
                value = 1 - value;
            }
            for (int r = 1; r < rows; r++) {
                int v = grid[r][c];
                if (flip_rows[r]) {
                    v = 1 - v;
                }
                if (v != value) {
                    return false;
                }
            }
        }
        return true;
    }
};