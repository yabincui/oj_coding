class Solution {
    
    int p[2000];
    
    int findRoot(int pos) {
        if (p[pos] == -1) {
            return pos;
        }
        return p[pos] = findRoot(p[pos]);
    }
    
    void unionRoot(int root1, int root2) {
        p[root1] = root2;
    }
    
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        memset(p, -1, sizeof(p));
        for (auto& v : edges) {
            int root1 = findRoot(v[0]);
            int root2 = findRoot(v[1]);
            if (root1 == root2) {
                return v;
            }
            unionRoot(root1, root2);
        }
    }
};