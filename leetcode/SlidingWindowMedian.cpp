template <typename T>	class AVLTree {	private:		struct AVLNode {			T value;			AVLNode* left;			AVLNode* right;			AVLNode* parent;			int height;			int size;		};			public:			typedef AVLNode node_type;			AVLTree() {			compareFunction_ = [](const T& t1, const T& t2) {				if (t1 < t2) return -1;				if (t2 < t1) return 1;				return 0;			};			root_ = NULL;		}		


AVLTree(const std::function<int(const T&, const T&)>& compareFunction) {			compareFunction_ = compareFunction;			root_ = NULL;		}	

~AVLTree() {			eraseTree(root_);		}				

bool empty() const {			return root_ == NULL;		}		

int size() const {			return getSize(root_);		}				

const AVLNode* getRoot() {			return root_;		}		

void insert(const T& value) {			AVLNode* parent = NULL;			AVLNode** cur = &root_;			while (*cur != NULL) {				parent = *cur;				int ret = compareFunction_(value, (*cur)->value);				if (ret <= 0) {					cur = &(*cur)->left;				} else {					cur = &(*cur)->right;				}			}			*cur = newNode(value, parent);			makeBalance(*cur);		}			AVLNode* findNode(const T& value) {						AVLNode* cur = root_;			while (cur) {				int ret = compareFunction_(value, cur->value);				if (ret == 0) {					return cur;				} else if (ret < 0) {					cur = cur->left;				} else {					cur = cur->right;				}			}			return cur;		}					AVLNode* lowerBoundNode(const T& value) {			AVLNode* result = NULL;			AVLNode* cur = root_;			while (cur) {				int ret = compareFunction_(value, cur->value);				if (ret <= 0) {					result = cur;					cur = cur->left;				} else {					cur = cur->right;				}			}			return result;		}					AVLNode* upperBoundNode(const T& value) {			AVLNode* result = NULL;			AVLNode* cur = root_;			while (cur) {				int ret = compareFunction_(value, cur->value);				if (ret < 0) {					result = cur;					cur = cur->left;				} else {					cur = cur->right;				}			}			return result;		}				T* find(const T& value) {			AVLNode* node = findNode(value);			if (node) {				return &node->value;			}			return NULL;		}						AVLNode* findNodeAtPosition(int position) {			if (position >= getSize(root_)) {				return NULL;			}			return findNodeAtPositionInner(root_, position);		}			void erase(const T& value) {			AVLNode* node = findNode(value);			if (node) {				erase(node);			}		}				void erase(AVLNode* node) {						if (node->left == NULL)	{				if (node->right == NULL) {					AVLNode* parent = node->parent;					replaceChild(parent, node, NULL);					delete node;					makeBalance(parent);				} else {					AVLNode* leafNode = findMin(node->right);					node->value = leafNode->value;					erase(leafNode);				}			} else {				AVLNode* leafNode = findMax(node->left);				node->value = leafNode->value;				erase(leafNode);			}					}			int findSizeInBetween(AVLNode* begin, AVLNode* end) {						if (begin == NULL) {				return 0;			}			if (end == NULL) {				end = findMax(root_);			}			if (compareFunction_(begin->value, end->value) > 0) {				return 0;			}			std::unordered_set<AVLNode*> set;			for (AVLNode* i = begin; i; i = i->parent) {				set.insert(i);			}			AVLNode* root = NULL;			for (AVLNode* i = end; i; i = i->parent) {				if (set.find(i) != set.end()) {					root = i;					break;				}			}			if (root == NULL) {				return 0;			}			int result = 1;			AVLNode* prev = begin->left;			for (AVLNode* i = begin; i != root; i = i->parent) {				if (i->left == prev) {										result += 1 + getSize(i->right);					}				prev = i;			}			prev = end->right;			for (AVLNode* i = end; i != root; i = i->parent) {				if (i->right == prev) {										result += 1 + getSize(i->left);				}				prev = i;			}			return result;		}		private:			AVLNode* newNode(const T& value, AVLNode* parent) {			AVLNode* node = new AVLNode;			node->value = value;			node->height = 0;			node->size = 1;			node->left = node->right = NULL;			node->parent = parent;			return node;		}				void makeBalance(AVLNode* cur) {			AVLNode* prev = NULL;			while (cur != NULL) {				fixHeight(cur);				fixSize(cur);				int leftHeight = getHeight(cur->left);					int rightHeight = getHeight(cur->right);				if (leftHeight - rightHeight == 2) {					int leftLeftHeight = getHeight(cur->left->left);					int leftRightHeight = getHeight(cur->left->right);					if (leftLeftHeight >= leftRightHeight) {						cur = cur->left;						RotateUp(cur);					} else {						cur = cur->left->right;						RotateUp(cur);						RotateUp(cur);					}				} else if (rightHeight - leftHeight == 2) {					int rightLeftHeight = getHeight(cur->right->left);					int rightRightHeight = getHeight(cur->right->right);					if (rightRightHeight >= rightLeftHeight) {						cur = cur->right;						RotateUp(cur);					} else {						cur = cur->right->left;						RotateUp(cur);						RotateUp(cur);					}				}				prev = cur;				cur = cur->parent;			}			root_ = prev;		}				int getHeight(AVLNode* node) {			return node ? node->height : -1;		}		void RotateUp(AVLNode* cur) {			AVLNode* k = cur->parent;			if (k == NULL) {				return;			}			AVLNode* parent = k->parent;			if (k->left == cur) {				k->left = cur->right;				if (k->left) {					k->left->parent = k;				}				cur->right = k;				k->parent = cur;			} else {				k->right = cur->left;				if (k->right) {					k->right->parent = k;				}				cur->left = k;				k->parent = cur;			}			replaceChild(parent, k, cur);			fixHeight(k);			fixHeight(cur);			fixHeight(parent);			fixSize(k);			fixSize(cur);			fixSize(parent);		}				void replaceChild(AVLNode* parent, AVLNode* old_child, AVLNode* new_child) {			if (new_child) {				new_child->parent = parent;			}			if (parent) {				if (parent->left == old_child) {					parent->left = new_child;				} else {					parent->right = new_child;				}			}		}				void fixHeight(AVLNode* node) {			if (node) {				node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;			}		}				int getSize(AVLNode* node) const {			return node ? node->size : 0;		}				void fixSize(AVLNode* node) {			if (node) {				node->size = getSize(node->left) + getSize(node->right) + 1;			}		}				AVLNode* findMin(AVLNode* node) {			if (node) {				while (node->left) {					node = node->left;				}			}			return node;		}		AVLNode* findMax(AVLNode* node) {			if (node) {				while (node->right) {					node = node->right;				}			}			return node;		}		void eraseTree(AVLNode* node) {			if (node) {				eraseTree(node->left);				eraseTree(node->right);				delete node;			}		}		AVLNode* findNodeAtPositionInner(AVLNode* cur, int position) {			if (getSize(cur->left) > position) {				return findNodeAtPositionInner(cur->left, position);			}			position -= getSize(cur->left);			if (position == 0) {				return cur;			}			position--;			return findNodeAtPositionInner(cur->right, position);		}		std::function<int(const T&, const T&)> compareFunction_;		AVLNode* root_;	};



class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        AVLTree<int> tree;
        vector<double> result;
        for (int i = 0; i < nums.size(); ++i) {
            tree.insert(nums[i]);
            if (i >= k) {
                tree.erase(nums[i-k]);
            }
            if (tree.size() == k) {
                if (k % 2 == 0) {
                    long long left = tree.findNodeAtPosition(k / 2 - 1)->value;
                    long long right = tree.findNodeAtPosition(k / 2)->value;
                    result.push_back((left + right) / 2.0);
                } else {
                    result.push_back(tree.findNodeAtPosition(k / 2)->value);
                }
            }
        }
        return result;
    }
};
