// 515. Find Largest Element in Each Row
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
    vector<int> res;
    
    vector<int> largestValues(TreeNode* root) {
        return findValueMostElement(root);
    }
    vector<int> findValueMostElement(TreeNode* root) {
        res.clear();
        recur(root, 0);
        return res;
    }
    
    void recur(TreeNode* r, int row) {
        if (r != NULL) {
            if (res.size() < row + 1) {
                res.resize(row + 1, INT_MIN);
            }
            if (res[row] < r->val) {
                res[row] = r->val;
            }
            recur(r->left, row + 1);
            recur(r->right, row + 1);
        }
    }
};
