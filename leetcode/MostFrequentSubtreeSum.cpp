// 508 Most Frequent Subtree Sum.
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
    unordered_map<int, int> hit_map;
    vector<int> findFrequentTreeSum(TreeNode* root) {
        hit_map.clear();
        visit(root);
        vector<int> res;
        int max_value = 0;
        for (auto& pair : hit_map) {
            if (pair.second > max_value) {
                max_value = pair.second;
                res.clear();
                res.push_back(pair.first);
            } else if (pair.second == max_value) {
                res.push_back(pair.first);
            }
        }
        return res;
    }

    int visit(TreeNode* r) {
        if (r != NULL) {
            int sum = visit(r->left) + visit(r->right) + r->val;
            hit_map[sum]++;
            return sum;
        }
        return 0;
    }
};
