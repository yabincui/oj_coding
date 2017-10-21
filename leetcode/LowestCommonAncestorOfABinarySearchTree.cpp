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
    
    int recur(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& found) {
        if (root == nullptr) return 0;
        int value = recur(root->left, p, q, found);
        if (root == p) {
            value |= 1;
        }
        if (root == q) {
            value |= 2;
        }
        value |= recur(root->right, p, q, found);
        if (value == 3 && found == nullptr) {
            found = root;
        }
        return value;
    }
    
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* found = nullptr;
        recur(root, p, q, found);
        return found;
    }
};