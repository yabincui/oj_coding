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
    
    TreeNode* deleteMin(TreeNode* root, TreeNode*& minNode) {
        if (root->left == NULL) {
            minNode = root;
            return root->right;
        }
        TreeNode* cur = root;
        while (cur->left->left != NULL) {
            cur = cur->left;
        }
        minNode = cur->left;
        cur->left = cur->left->right;
        return root;
    }
    
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == NULL) {
            return root;
        }
        TreeNode* ret = root;
        if (root->val == key) {
            if (root->left == NULL) {
                ret = root->right;
            } else if (root->right == NULL) {
                ret = root->left;
            } else {
                TreeNode* minRight;
                root->right = deleteMin(root->right, minRight);
                ret = minRight;
                ret->left = root->left;
                ret->right = root->right;
            }
            delete root;
        } else if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else {
            root->right = deleteNode(root->right, key);
        }
        
        return ret;
    }
};
