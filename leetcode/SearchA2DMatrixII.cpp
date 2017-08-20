class Solution {
    
    bool find(vector<vector<int>>& matrix, int left, int top, int right, int bottom, int target) {
        //printf("find left %d, top %d, right %d, bottom %d\n", left, top, right, bottom);
        if (left > right || top > bottom) {
            return false;
        }
        int midC = (left + right) / 2;
        int midR = (top + bottom) / 2;
        int value = matrix[midR][midC];
        if (value == target) {
            return true;
        }
        if (value > target) {
            return find(matrix, left, top, midC - 1, bottom, target) || find(matrix, midC, top, right, midR - 1, target);
        }
        return find(matrix, left, midR + 1, right, bottom, target) || find(matrix, midC + 1, top, right, midR, target);
    }
    
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        if (rows == 0) return false;
        int cols = matrix[0].size();
        if (cols == 0) return false;
        return find(matrix, 0, 0, cols - 1, rows - 1, target);
    }
};
