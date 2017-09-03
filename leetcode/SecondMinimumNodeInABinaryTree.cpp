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
    
private:
    int recur(TreeNode* root, int minValue) {
        if (root == NULL) return -1;
        if (root->val > minValue) {
            return root->val;
        }
        int a = recur(root->left, minValue);
        int b = recur(root->right, minValue);
        if (a < 0) return b;
        if (b < 0) return a;
        return min(a, b);
    }
    
public:
    int findSecondMinimumValue(TreeNode* root) {
        if (root == NULL) return -1;
        int minValue = root->val;
        return recur(root, minValue);
    }
};
