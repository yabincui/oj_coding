class NumMatrix {
    
    vector<vector<int64_t>> sum;
    
public:
    NumMatrix(vector<vector<int>> matrix) {
        int rows = matrix.size();
        if (rows == 0) return;
        int cols = matrix[0].size();
        if (cols == 0) return;
        sum.resize(rows + 1, vector<int64_t>(cols + 1));
        for (int r = 1; r <= rows; ++r) {
            for (int c = 1; c <= cols; ++c) {
                sum[r][c] = sum[r-1][c] + matrix[r-1][c-1];
            }
        }
        for (int c = 1; c <= cols; ++c) {
            for (int r = 1; r <= rows; ++r) {
                sum[r][c] += sum[r][c-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2 + 1][col2 + 1] - sum[row1][col2 + 1] - sum[row2 + 1][col1] + sum[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */