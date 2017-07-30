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
    
    int getAllNodes(TreeNode* root, vector<pair<int, TreeNode*>>& nodes) {
        if (root) {
            int h = max(getAllNodes(root->left, nodes), getAllNodes(root->right, nodes)) + 1;
            nodes.push_back(make_pair(h, root));
            return h;
        }
        return 0;
    }

    unordered_map<TreeNode*, int> same_map;
    
    bool isSame(TreeNode* a, TreeNode* b) {
        if (a == nullptr && b == nullptr) {
            return true;
        } else if (a == nullptr || b == nullptr) {
            return false;
        }
        if (a->val != b->val) return false;
        return same_map[a] == same_map[b];
    }
    
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        same_map.clear();   
        vector<pair<int, TreeNode*>> nodes;
        getAllNodes(root, nodes);
        sort(nodes.begin(), nodes.end());

        vector<pair<int, TreeNode*>> unique_nodes;
        vector<int> count;
        for (int i = 0; i < nodes.size(); ++i) {
            TreeNode* a = nodes[i].second;
            bool unique = true;
            for (int j = (int)unique_nodes.size() - 1; j >= 0 && unique_nodes[j].first == nodes[i].first; --j) {
                TreeNode* b = unique_nodes[j].second;
                if (a->val == b->val && isSame(a->left, b->left) && isSame(a->right, b->right)) {
                    same_map[a] = j;
                    unique = false;
                    count[j]++;
                    break;
                }
            }
            if (unique) {
                //printf("i = %d, h = %d, val = %d\n", i, nodes[i].first, a->val);
                same_map[a] = unique_nodes.size();
                unique_nodes.push_back(nodes[i]);
                count.push_back(1);
            }
        }
        vector<TreeNode*> res;
        for (int i = 0; i < unique_nodes.size(); ++i) {
            if (count[i] > 1) {
                res.push_back(unique_nodes[i].second);
            }
        }
        return res;
    }
};
