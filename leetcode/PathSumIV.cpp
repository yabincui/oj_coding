class Solution {
    
    bool hasValue(vector<vector<int>>& tree, int depth, int pos) {
        if (depth >= tree.size()) {
            return false;
        }
        if (tree[depth].size() <= pos) {
            return false;
        }
        if (tree[depth][pos] == -1) {
            return false;
        }
        return true;
    }
    
    int recur(vector<vector<int>>& tree, int depth, int pos, int path_sum) {
        bool hasChild = false;
        path_sum += tree[depth][pos];
        int sum = 0;
        if (hasValue(tree, depth + 1, 2 * pos)) {
            hasChild = true;
            sum += recur(tree, depth + 1, 2 * pos, path_sum);
        }
        if (hasValue(tree, depth + 1, 2 * pos + 1)) {
            hasChild = true;
            sum += recur(tree, depth + 1, 2 * pos + 1, path_sum);
        }
        if (!hasChild) {
            sum += path_sum;
        }
        return sum;
    }
    
public:
    int pathSum(vector<int>& nums) {
        vector<vector<int>> tree;
        for (int num : nums) {
            int depth = num / 100;
            int pos = num / 10 % 10 - 1;
            int value = num % 10;
            if (tree.size() < depth) {
                tree.resize(depth);
            }
            vector<int>& level = tree[depth - 1];
            if (level.size() < pos + 1) {
                level.resize(pos + 1, -1);
            }
            level[pos] = value;
        }
        int sum = recur(tree, 0, 0, 0);
        return sum;
    }
};
