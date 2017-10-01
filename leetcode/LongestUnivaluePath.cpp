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
    
    int maxLen;

    int recur(TreeNode* root) {
        if (!root) {
            return -1;
        }
        int leftLen = 0;
        int leftValue = 0;
        if (root->left) {
            leftValue = root->left->val;
            leftLen = recur(root->left);
        }
        int rightLen = 0;
        int rightValue = 0;
        if (root->right) {
            rightValue = root->right->val;
            rightLen = recur(root->right);
        }
        if (leftValue == root->val) {
            if (root->val == rightValue) {
                maxLen = max(maxLen, leftLen + rightLen + 1);
                return max(leftLen, rightLen) + 1;
            }
            maxLen = max(maxLen, leftLen + 1);
            return leftLen + 1;
        }
        if (rightValue == root->val) {
            maxLen = max(maxLen, rightLen + 1);
            return rightLen + 1;
        }
        maxLen = max(maxLen, 1);
        return 1;
    }
    
public:
    int longestUnivaluePath(TreeNode* root) {
        maxLen = 0;
        recur(root);
        return max(0, maxLen - 1);
    }
};
