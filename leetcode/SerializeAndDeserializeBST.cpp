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
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // V\d+ is a value of a node.
        // N represents null.
        // using prefix order to visit the tree.
        string res;
        serialize_r(root, res);
        //printf("res = %s\n", res.c_str());
        return res;
    }
    
    void serialize_r(TreeNode* root, string& s) {
        if (root == NULL) {
            s += "N";
        } else {
            s += "V" + to_string(root->val);
            serialize_r(root->left, s);
            serialize_r(root->right, s);
        }
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        const char* p = data.c_str();
        return deserialize_r(p);
    }
    
    TreeNode* deserialize_r(const char*& p) {
        if (*p == '\0') {
            return NULL;
        }
        if (*p == 'N') {
            p++;
            return NULL;
        }
        if (*p == 'V') {
            char* end;
            int value = (int)strtol(p + 1, &end, 10);
            //printf("value = %d\n", value);
            p = end;
            TreeNode* n = new TreeNode(value);
            n->left = deserialize_r(p);
            n->right = deserialize_r(p);
            return n;
        }
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
