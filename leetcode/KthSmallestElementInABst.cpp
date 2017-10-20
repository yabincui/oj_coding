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
    
    int found;
    
    void recur(TreeNode* root, int& k) {
        if (root->left) {
            recur(root->left, k);
        }
        if (k == 0) {
            return;
        }
        if (k == 1) {
            found = root->val;
            k--;
            return;
        }
        k--;
        if (root->right) {
            recur(root->right, k);
        }
    }
    
public:
    int kthSmallest(TreeNode* root, int k) {
        recur(root, k);
        return found;
    }
};