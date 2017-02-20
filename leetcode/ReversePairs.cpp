// 493 Reverse Pairs
class Solution {
public:
    struct Node {
        int val;
        int min_val;
        int max_val;
        int count;
        Node* left;
        Node* right;
        
        Node(int val = 0) : val(val), min_val(val), max_val(val), count(1), left(NULL), right(NULL) {}
    };
    
    int findBiggerCount2(Node* tree, int64_t val) {
        if (tree != NULL) {
            if (tree->val > val) {
                return 1 + findBiggerCount(tree->left, val) + findBiggerCount(tree->right, val);
            } else if (tree->val <= val) {
                return findBiggerCount(tree->right, val);
            }
        }
        return 0;
    }
    
    int findBiggerCount(Node* tree, int64_t val) {
        int res = 0;
        while (tree != NULL) {
            //printf("find tree->val = %d, min_val = %d, max_val = %d, count %d val = %lld\n", tree->val, tree->min_val, tree->max_val, tree->count, (unsigned long long)val);
            if (tree->max_val <= val) {
                break;
            } else if (tree->min_val > val) {
                res += tree->count;
                break;
            } else {
                if (tree->val > val) {
                    res += 1 + findBiggerCount(tree->left, val);
                }
                tree = tree->right;
            }
        }
        return res;
    }
    
    void insertTree(Node*& tree, int val) {
        if (tree == NULL) {
            tree = new Node(val);
        } else if (tree->val <= val) {
            insertTree(tree->right, val);
            tree->count++;
        } else if (tree->val > val) {
            insertTree(tree->left, val);
            tree->count++;
        }
    }
    
    void insertTree(Node** tree, Node* n) {
        Node** p = tree;
        while (*p != NULL) {
            (*p)->count++;
            (*p)->min_val = min((*p)->min_val, n->val);
            (*p)->max_val = max((*p)->max_val, n->val);
            if ((*p)->val > n->val) {
                p = &((*p)->left);
            } else {
                p = &((*p)->right);
            }
        }
        *p = n;
    }
    
    
    
    void freeTree(Node* tree) {
        if (tree != NULL) {
            freeTree(tree->left);
            freeTree(tree->right);
            delete tree;
        }
    }

    int reversePairs(vector<int>& nums) {
       vector<Node> v(nums.size());
       for (int i = 0; i < nums.size(); ++i) {
           v[i].val = nums[i];
           v[i].min_val = nums[i];
           v[i].max_val = nums[i];
       }
       Node* tree = NULL;
       int res = 0;
       for (int i = 0; i < nums.size(); ++i) {
           int64_t val = (int64_t)nums[i] * 2;
           res += findBiggerCount(tree, val);
           insertTree(&tree, &v[i]);
       }
       //freeTree(tree);
       return res;
    }
};
