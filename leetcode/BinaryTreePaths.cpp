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
    void recur(TreeNode* root, vector<int>& path, vector<string>& res) {
        path.push_back(root->val);
        if (root->left) {
            recur(root->left, path, res);
        }
        if (root->right) {
            recur(root->right, path, res);
        }
        if (root->left == nullptr && root->right == nullptr) {
            string s;
            for (int i = 0; i < path.size(); ++i) {
                s += to_string(path[i]);
                if (i + 1 != path.size()) {
                    s += "->";
                }
            }
            res.push_back(s);
        }
        path.pop_back();
    }
    
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<int> path;
        vector<string> res;
        if (root == nullptr) {
            return res;
        }
        recur(root, path, res);
        return res;
    }
};