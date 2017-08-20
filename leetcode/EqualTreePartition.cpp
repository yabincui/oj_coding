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
    
    int getSum(TreeNode* root, unordered_map<int, int>& sum_map) {
        if (root == NULL) {
            return 0;
        }
        int sum = root->val;
        sum += getSum(root->left, sum_map);
        sum += getSum(root->right, sum_map);
        sum_map[sum]++;
        return sum;
    }
    
public:
    bool checkEqualTree(TreeNode* root) {
        unordered_map<int, int> sum_map;
        int sum = getSum(root, sum_map);
        if (sum == 0) {
            return sum_map[0] > 1;
        }
        if (sum % 2 != 0) {
            return false;
        }
        return sum_map.find(sum / 2) != sum_map.end();
    }
};
