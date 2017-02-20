// 295. Find Median from Data Stream
class MedianFinder {
private:
    struct Node {
        int val;
        int size;
        Node* left, *right;  
    };
    
    void insertTree(Node*& root, int val) {
        Node** pp = &root;
        while (*pp != NULL) {
            (*pp)->size++;
            if (val <= (*pp)->val) {
                pp = &(*pp)->left;
            } else {
                pp = &(*pp)->right;
            }
        }
        *pp = new Node;
        (*pp)->val = val;
        (*pp)->size = 1;
        (*pp)->left = (*pp)->right = NULL;
    }
    
    int findValueAtPos(Node* root, int pos) {
        while (true) {
            int left_size = (root->left) ? root->left->size : 0;
            if (left_size == pos) {
                return root->val;
            } else if (left_size > pos) {
                root = root->left;
            } else {
                pos -= left_size + 1;
                root = root->right;
            }
        }
    }
    
    void deleteTree(Node* root) {
        if (root != NULL) {
          deleteTree(root->left);
          deleteTree(root->right);
          delete root;
        }
    }
    
    Node* root;
    
public:
    /** initialize your data structure here. */
    MedianFinder() {
        root = NULL;    
    }
    
    ~MedianFinder() {
        deleteTree(root);
    }
    
    void addNum(int num) {
        insertTree(root, num);
    }
    
    double findMedian() {
        if (root == NULL) {
            return 0;
        }
        int size = root->size;
        if (size % 2 == 0) {
            int pos1 = size / 2 - 1;
            int pos2 = size / 2;
            int a = findValueAtPos(root, pos1);
            int b = findValueAtPos(root, pos2);
            return (double)(a + b) / 2;
        } else {
            int pos = size / 2;
            int a = findValueAtPos(root, pos);
            return (double)a;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */
