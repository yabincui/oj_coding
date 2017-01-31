// 404. Sum of Left Leaves
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
public:
    int sumOfLeftLeaves(TreeNode* root) {
        int sum = getSum(root, false);
        return sum;
    }
    
    int getSum(TreeNode* root, bool is_left) {
        int sum = 0;
        if (root != NULL) {
            sum += getSum(root->left, true);
            sum += getSum(root->right, false);
            if (root->left == NULL && root->right == NULL && is_left) {
                sum += root->val;
            }
        }
        return sum;
    }
};
