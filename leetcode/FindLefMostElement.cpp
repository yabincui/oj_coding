// 513 Find Left Most Element
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
    int last_row;
    int value;
    int findBottomLeftValue(TreeNode* root) {
        return findLeftMostNode(root);
    }
    int findLeftMostNode(TreeNode* root) {
        last_row = -1;
        recur(root, 0);
        return value;
    }
    void recur(TreeNode* r, int row) {
        if (r != NULL) {
            recur(r->left, row+1);
            recur(r->right, row+1);
            if (row > last_row) {
                last_row = row;
                value = r->val;
            }
        }
    }
};
