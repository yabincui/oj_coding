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
    
    TreeNode* res;
    
    int find_r(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return 0;
        }
        int ret = 0;
        if (root == p) {
            ret |= 1;
        }
        if (root == q) {
            ret |= 2;
        }
        ret |= find_r(root->left, p, q);
        ret |= find_r(root->right, p, q);
        if (ret == 3 && res == nullptr) {
            res = root;
        }
        return ret;
    }
    
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        res = nullptr;
        find_r(root, p, q);
        return res;
    }
};
