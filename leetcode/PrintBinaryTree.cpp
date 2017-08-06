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
    
    int findMax(vector<int>& nums, int begin, int end) {
        int maxIdx = begin;
        for (int i = begin + 1; i <= end; ++i) {
            if (nums[i] > nums[maxIdx]) {
                maxIdx = i;
            }
        }
        return maxIdx;
    }
    
    TreeNode* recur(vector<int>& nums, int begin, int end) {
        if (begin > end) {
            return NULL;
        }
        int mid = findMax(nums, begin, end);
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = recur(nums, begin, mid - 1);
        root->right = recur(nums, mid + 1, end);
        return root;
    }
    
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.empty()) return NULL;
        return recur(nums, 0, nums.size() - 1);
    }
};
