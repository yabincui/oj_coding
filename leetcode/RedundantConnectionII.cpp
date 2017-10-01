class Solution {
    
    int parent[1001];
    int treeParent[1001];
    
    int findRoot(int p) {
        if (parent[p] == -1) {
            return p;
        }
        return parent[p] = findRoot(parent[p]);
    }
    
    
    bool check(vector<vector<int>>& edges, int omitIndex) {
        memset(parent, -1, sizeof(parent));
        memset(treeParent, -1, sizeof(treeParent));
        for (int i = 0; i < edges.size(); ++i) {
            if (i == omitIndex) continue;
            auto& v = edges[i];
            int root1 = findRoot(v[0]);
            int root2 = findRoot(v[1]);
            if (root1 == root2) {
                return false;
            }
            parent[root1] = root2;
            if (treeParent[v[1]] != -1) {
                return false;
            }
            treeParent[v[1]] = v[0];
        }
        return true;
    }
    
    
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        for (int i = edges.size() - 1; i >= 0; --i) {
            if (check(edges, i)) {
                return edges[i];
            }
        }
        

        
    }
};
