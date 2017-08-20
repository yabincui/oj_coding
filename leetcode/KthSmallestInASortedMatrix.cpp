class Solution {
    
    int cols;
    
    struct Pos {
        int r, c;
        Pos(int r, int c) : r(r), c(c) {}
    };
    
    Pos getPos(int value) {
        return Pos(value / cols, value % cols);
    }
    int getValue(const Pos& p) {
        return p.r * cols + p.c;
    }
    
    static bool compPair(pair<int, int>& p1, pair<int, int>& p2) {
        return p1.first > p2.first;
    }
    
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int rows = matrix.size();
        if (rows == 0) return -1;
        int cols = matrix[0].size();
        this->cols = cols;
        if (cols == 0) return -1;
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&compPair)> q(compPair);
        for (int r = 0; r < rows; ++r) {
            q.push(make_pair(matrix[r][0], getValue(Pos(r, 0))));
        }
        for (int i = 1; i < k; ++i) {
            auto pair = q.top(); q.pop();
            Pos p = getPos(pair.second);
            if (p.c + 1 < cols) {
                q.push(make_pair(matrix[p.r][p.c + 1], getValue(Pos(p.r, p.c + 1))));
            }
        }
        return q.top().first;
    }
};
