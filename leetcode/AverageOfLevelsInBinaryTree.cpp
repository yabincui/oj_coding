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
    
    vector<double> sum;
    vector<int> count;
    
    void visit_r(TreeNode* node, int depth) {
        if (node == NULL) return;
        if (depth == sum.size()) {
            sum.push_back(0);
            count.push_back(0);
        }
        sum[depth] += node->val;
        count[depth]++;
        visit_r(node->left, depth + 1);
        visit_r(node->right, depth + 1);
    }
    
public:
    vector<double> averageOfLevels(TreeNode* root) {
        sum.clear();
        count.clear();
        visit_r(root, 0);
        for (int i = 0; i < count.size(); ++i) {
            sum[i] /= count[i];
        }
        return sum;
    }
};
