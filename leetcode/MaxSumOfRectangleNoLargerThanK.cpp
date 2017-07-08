class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        // from a start point, end point, there are O(n^4) possibilities.
        // min value in a range. or possible values in a range. use unordered_map? map.
        // first select two columns, O(COLS^2), then get one array of numbers, put them in a sorted array, use binary search to find best one.
        // O(COLS^2 * ROWS * log(ROWS))
        int rows = matrix.size();
        if (rows == 0) return 0;
        int cols = matrix[0].size();
        if (cols == 0) return 0;
        vector<vector<int>> line_sum(rows, vector<int>(cols, 0));  // line_sum[i][j] = matrix[i][0..j]
        for (int r = 0; r < rows; ++r) {
            line_sum[r][0] = matrix[r][0];
            for (int c = 1; c < cols; ++c) {
                line_sum[r][c] = matrix[r][c] + line_sum[r][c-1];
            }
        }
        bool has_result = false;
        int result = INT_MIN;

        vector<int> s(rows, 0);
        for (int c1 = 0; c1 < cols; ++c1) {
            for (int c2 = c1; c2 < cols; ++c2) {
                for (int r = 0; r < rows; ++r) {
                    s[r] = line_sum[r][c2] - (c1 == 0 ? 0 : line_sum[r][c1 - 1]);
                    if (r > 0) {
                        s[r] += s[r-1];
                    }
                }
                set<int> hit_set;
                hit_set.insert(0);
                for (int r = 0; r < rows; ++r) {
                    
                    auto it = hit_set.lower_bound(s[r] - k);
                    if (it != hit_set.end()) {
                        if (!has_result) {
                            has_result = true;
                            result = s[r] - *it;
                        } else {
                            result = max(result, s[r] - *it);
                        }
                        //printf("r = %d, c1 = %d, c2 = %d, result = %d, s[%d] = %d, *it = %d\n", r, c1, c2, result, r, s[r], it != hit_set.end() ? *it : INT_MIN);
                    }
                    hit_set.insert(s[r]);
                }
            }
        }
        return result;
    }
};
