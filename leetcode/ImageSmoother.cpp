class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        int rows = M.size();
        if (rows == 0) return M;
        int cols = M[0].size();
        if (cols == 0) return M;
        vector<vector<int>> res(rows, vector<int>(cols, 0));
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int sum = 0;
                int count = 0;
                for (int nr = r - 1; nr <= r + 1; ++nr) {
                    for (int nc = c - 1; nc <= c + 1; ++nc) {
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                            sum += M[nr][nc];
                            count++;
                        }
                    }
                }
                res[r][c] = sum / count;
            }
        }
        return res;
    }
};
