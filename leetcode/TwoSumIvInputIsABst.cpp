/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    
    void visit(TreeNode* root, unordered_map<int, int>& map) {
        if (root) {
            map[root->val]++;
            visit(root->left, map);
            visit(root->right, map);
        }
    }
    
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_map<int, int> map;
        visit(root, map);
        for (auto& pair : map) {
            int t = k - pair.first;
            if (t == pair.first) {
                if (pair.second > 1) {
                    return true;
                }
            } else {
                if (map.find(t) != map.end()) {
                    return true;
                }
            }
        }
        return false;
    }
};
