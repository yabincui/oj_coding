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
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        return recur(root, 1, v, d, true);
    }
    
    TreeNode* recur(TreeNode* cur, int depth, int v, int d, bool is_left) {
        if (depth > d) {
            return cur;
        }
        if (cur == NULL && depth < d) {
            return NULL;
        }
        if (depth < d) {
            cur->left = recur(cur->left, depth + 1, v, d, true);
            cur->right = recur(cur->right, depth + 1, v, d, false);
            return cur;
        }
        TreeNode* node = new TreeNode(v);
        if (is_left) {
            node->left = recur(cur, depth + 1, v, d, true);
        } else {
            node->right = recur(cur, depth + 1, v, d, false);
        }
        return node;
    }
};
