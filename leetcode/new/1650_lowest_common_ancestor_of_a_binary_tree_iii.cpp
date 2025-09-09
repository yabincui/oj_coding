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
    Node* lowestCommonAncestor(Node* p, Node * q) {
        if (p == nullptr || q == nullptr) {
            return nullptr;
        }
        unordered_set<Node*> p_ancestor;
        while (p != nullptr) {
            p_ancestor.insert(p);
            p = p->parent;
        }
        while (q != nullptr) {
            if (p_ancestor.count(q) != 0) {
                return q;
            }
            q = q->parent;
        }
        return nullptr;
    }
};