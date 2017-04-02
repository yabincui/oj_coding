// 547. Friend Circles
class Solution {
    
    int s[200];
    
    int findRoot(int a) {
        if (s[a] == -1) {
            return a;
        }
        return s[a] = findRoot(s[a]);
    }
    
    void unionSet(int a, int b) {
        int root1 = findRoot(a);
        int root2 = findRoot(b);
        if (root1 != root2) {
            s[root1] = root2;
        }
    }
    
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        if (n == 0) return 0;
        for (int i = 0; i < n; ++i) {
            s[i] = -1;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (M[i][j] == 1) {
                    unionSet(i, j);
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (-1 == s[i]) {
                res++;
            }
        }
        return res;
    }
};
