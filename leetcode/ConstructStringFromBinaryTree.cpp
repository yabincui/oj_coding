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
    string tree2str(TreeNode* t) {
        string s;
        recur(t, s);
        return s;
    }
    
    void recur(TreeNode* t, string& s) {
        if (t == NULL) {
            return;
        }
        s += to_string(t->val);
        if (t->left == NULL && t->right == NULL) {
            return;
        }
        if (t->left != NULL && t->right == NULL) {
            s.push_back('(');
            recur(t->left, s);
            s.push_back(')');
        } else if (t->left != NULL && t->right != NULL) {
            s.push_back('(');
            recur(t->left, s);
            s.push_back(')');
            s.push_back('(');
            recur(t->right, s);
            s.push_back(')');
        } else if (t->left == NULL && t->right != NULL) {
            s.push_back('(');
            s.push_back(')');
            s.push_back('(');
            recur(t->right, s);
            s.push_back(')');
        }
    }
};
