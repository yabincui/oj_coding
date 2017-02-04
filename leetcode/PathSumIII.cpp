// 437. Path Sum III
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
    int sum;
    int pathSum(TreeNode* root, int sum) {
        vector<int> path;
        this->sum = sum;
        return recur(root, path);
    }

    int recur(TreeNode* root, vector<int>& path) {
        if (root != nullptr) {
            path.push_back(root->val);
            int cur = 0;
            int res = 0;
            for (int i = path.size() - 1; i >= 0; --i) {
                cur += path[i];
                if (cur == sum) {
                    res++;
                }
            }
            res += recur(root->left, path);
            res += recur(root->right, path);
            path.pop_back();
            return res;
        }
        return 0;
    }
};
