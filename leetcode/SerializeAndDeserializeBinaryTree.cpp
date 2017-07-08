/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
    
    void serialize_r(TreeNode* node, string& s) {
        if (node == NULL) {
            return;
        }
        s += to_string(node->val);
        s += node->left ? 'L' : 'N';
        s += node->right ? 'R' : 'N';
        
        if (node->left != NULL) {
            serialize_r(node->left, s);
        }
        if (node->right != NULL) {
            serialize_r(node->right, s);
        }
    }
    
    TreeNode* deserialize_r(const char*& p) {
        if (*p == '\0') {
            return NULL;
        }
        int value = (int)strtol(p, (char**)&p, 10);
        TreeNode* root = new TreeNode(value);
        bool has_left = *p++ == 'L';
        bool has_right = *p++ == 'R';
        if (has_left) {
            root->left = deserialize_r(p);
        }
        if (has_right) {
            root->right = deserialize_r(p);
        }
        return root;
    }
    
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        serialize_r(root, s);
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        const char* p = data.c_str();
        TreeNode* root = deserialize_r(p);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
