// 501. Find Mode In Binary Tree
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
    unordered_map<int, int> map;
    vector<int> findMode(TreeNode* root) {
        map.clear();
        travel(root);
        vector<int> result;
        int max_value = 0;
        for (auto pair : map) {
            if (pair.second < max_value) {
                continue;
            } else if (pair.second > max_value) {
                max_value = pair.second;
                result.clear();
            }
            result.push_back(pair.first);
        }
        return result;
    }
    
    void travel(TreeNode* root) {
        if (root != NULL) {
            map[root->val]++;
            travel(root->left);
            travel(root->right);
        }
    }
    
    
};
