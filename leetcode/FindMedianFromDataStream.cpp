// 295. Find Median from Data Stream
/*
// Use Binary search tree to store a sorted list.
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
*/

// Use two priority queue to store the medians of the list.
class MedianFinder {
private:
    priority_queue<int, vector<int>> small_q;
    priority_queue<int, vector<int>, greater<int>> big_q;
    
public:
    MedianFinder() {
    }
    
    void addNum(int num) {
        if (small_q.empty() || small_q.top() >= num) {
            small_q.push(num);
        } else {
            big_q.push(num);
        }
        if (small_q.size() < big_q.size()) {
            small_q.push(big_q.top());
            big_q.pop();
        } else if (small_q.size() > big_q.size() + 1) {
            big_q.push(small_q.top());
            small_q.pop();
        }
    }
    
    double findMedian() {
        int size = small_q.size() + big_q.size();
        if (size % 2 == 0) {
            return ((double)small_q.top() + big_q.top()) / 2;
        }
        return small_q.top();
    }
};


/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */
