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
    
    pair<int, int> recur(TreeNode* root) {
        if (root == nullptr) {
            return make_pair(0, 0);
        }
        pair<int, int> left = recur(root->left);
        pair<int, int> right = recur(root->right);
        pair<int, int> res;
        res.first = root->val + left.second + right.second;
        res.second = max(left.first, left.second) + max(right.first, right.second);
        return res;
    }
    
public:
    int rob(TreeNode* root) {
        auto p = recur(root);
        return max(p.first, p.second);
    }
};