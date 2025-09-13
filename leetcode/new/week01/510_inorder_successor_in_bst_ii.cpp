// key: tree
// no error
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {
public:
    Node* inorderSuccessor(Node* node) {
        // the leftest child of node->right.
        if (node == nullptr) {
            return nullptr;
        }
        if (node->right) {
            Node* p = node->right;
            while (p->left) {
                p = p->left;
            }
            return p;
        }
        // or go to node->parent until see node is the left child of the ancestor.
        Node* parent = node->parent;
        while (parent != nullptr && parent->right == node) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }
};