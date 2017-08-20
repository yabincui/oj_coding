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
    
    void recur(TreeNode* root, int depth, int curPos, vector<int>& leftmost, vector<int>& rightmost) {
        if (root == NULL) return;
        if (leftmost.size() == depth) {
            leftmost.push_back(curPos);
            rightmost.push_back(curPos);
        } else {
            leftmost[depth] = min(leftmost[depth], curPos);
            rightmost[depth] = max(rightmost[depth], curPos);
        }
        recur(root->left, depth + 1, curPos * 2, leftmost, rightmost);
        recur(root->right, depth + 1, curPos * 2 + 1, leftmost, rightmost);
    }
    
public:
    int widthOfBinaryTree(TreeNode* root) {
        vector<int> leftmost;
        vector<int> rightmost;
        recur(root, 0, 0, leftmost, rightmost);
        int res = 0;
        for (int i = 0; i < leftmost.size(); ++i) {
            res = max(res, rightmost[i] - leftmost[i] + 1);
        }
        return res;
    }
};
