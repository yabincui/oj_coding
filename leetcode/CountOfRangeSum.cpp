template <typename T>
class AVLTree {
private:
	struct AVLNode {
		T value;
		AVLNode* left;
		AVLNode* right;
		AVLNode* parent;
		int height;
		int size;
	};
public:
	AVLTree() {
		compareFunction_ = [](const T& t1, const T& t2) {
			if (t1 < t2) return -1;
			if (t2 < t1) return 1;
			return 0;
		};
		root_ = NULL;
	}
	~AVLTree() {
		eraseTree(root_);
	}
	void insert(const T& value) {
		//printf("insert %d\n", value);
		AVLNode* parent = NULL;
		AVLNode** cur = &root_;
		while (*cur != NULL) {
			parent = *cur;
			int ret = compareFunction_(value, (*cur)->value);
			if (ret <= 0) {
				cur = &(*cur)->left;
			} else {
				cur = &(*cur)->right;
			}
		}
		*cur = newNode(value, parent);
		makeBalance(*cur);
		//checkValid();
	}
	// Find lowest node >= value.
	AVLNode* lowerBoundNode(const T& value) {
		AVLNode* result = NULL;
		AVLNode* cur = root_;
		while (cur) {
			int ret = compareFunction_(value, cur->value);
			if (ret <= 0) {
				result = cur;
				cur = cur->left;
			} else {
				cur = cur->right;
			}
		}
		return result;
	}

	// Find lowest node > value.
	AVLNode* upperBoundNode(const T& value) {
		AVLNode* result = NULL;
		AVLNode* cur = root_;
		while (cur) {
			int ret = compareFunction_(value, cur->value);
			if (ret < 0) {
				result = cur;
				cur = cur->left;
			} else {
				cur = cur->right;
			}
		}
		return result;
	}
	
	void erase(const T& value) {
		AVLNode* node = findNode(value);
		if (node) {
			erase(node);
		}
	}
	int findSizeInBetween(AVLNode* begin, AVLNode* end) {
		if (begin == NULL) {
			return 0;
		}
		if (end == NULL) {
			end = findMax(root_);
		}
		if (compareFunction_(begin->value, end->value) > 0) {
			return 0;
		}
		std::unordered_set<AVLNode*> set;
		for (AVLNode* i = begin; i; i = i->parent) {
			set.insert(i);
		}
		AVLNode* root = NULL;
		for (AVLNode* i = end; i; i = i->parent) {
			if (set.find(i) != set.end()) {
				root = i;
				break;
			}
		}
		if (root == NULL) {
			return 0;
		}
		int result = 1;
		AVLNode* prev = begin->left;
		for (AVLNode* i = begin; i != root; i = i->parent) {
			if (i->left == prev) {
				result += 1 + getSize(i->right);	
			}
			prev = i;
		}
		prev = end->right;
		for (AVLNode* i = end; i != root; i = i->parent) {
			if (i->right == prev) {
				result += 1 + getSize(i->left);
			}
			prev = i;
		}
		return result;
	}
private:
	AVLNode* newNode(const T& value, AVLNode* parent) {
		AVLNode* node = new AVLNode;
		node->value = value;
		node->height = 0;
		node->size = 1;
		node->left = node->right = NULL;
		node->parent = parent;
		return node;
	}
	
	void makeBalance(AVLNode* cur) {
		AVLNode* prev = NULL;
		while (cur != NULL) {
			fixHeight(cur);
			fixSize(cur);
			int leftHeight = getHeight(cur->left);	
			int rightHeight = getHeight(cur->right);
			if (leftHeight - rightHeight == 2) {
				int leftLeftHeight = getHeight(cur->left->left);
				int leftRightHeight = getHeight(cur->left->right);
				if (leftLeftHeight >= leftRightHeight) {
					cur = cur->left;
					RotateUp(cur);
				} else {
					cur = cur->left->right;
					RotateUp(cur);
					RotateUp(cur);
				}
			} else if (rightHeight - leftHeight == 2) {
				int rightLeftHeight = getHeight(cur->right->left);
				int rightRightHeight = getHeight(cur->right->right);
				if (rightRightHeight >= rightLeftHeight) {
					cur = cur->right;
					RotateUp(cur);
				} else {
					cur = cur->right->left;
					RotateUp(cur);
					RotateUp(cur);
				}
			}
			prev = cur;
			cur = cur->parent;
		}
		root_ = prev;
	}
	
	int getHeight(AVLNode* node) {
		return node ? node->height : -1;
	}
	
	void RotateUp(AVLNode* cur) {
		AVLNode* k = cur->parent;
		if (k == NULL) {
			return;
		}
		AVLNode* parent = k->parent;
		if (k->left == cur) {
			k->left = cur->right;
			if (k->left) {
				k->left->parent = k;
			}
			cur->right = k;
			k->parent = cur;
		} else {
			k->right = cur->left;
			if (k->right) {
				k->right->parent = k;
			}
			cur->left = k;
			k->parent = cur;
		}
		replaceChild(parent, k, cur);
		fixHeight(k);
		fixHeight(cur);
		fixHeight(parent);
		fixSize(k);
		fixSize(cur);
		fixSize(parent);
	}
	
	void replaceChild(AVLNode* parent, AVLNode* old_child, AVLNode* new_child) {
		if (new_child) {
			new_child->parent = parent;
		}
		if (parent) {
			if (parent->left == old_child) {
				parent->left = new_child;
			} else {
				parent->right = new_child;
			}
		}
	}
	
	void fixHeight(AVLNode* node) {
		if (node) {
			node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
		}
	}
	
	int getSize(AVLNode* node) {
		return node ? node->size : 0;
	}
	
	void fixSize(AVLNode* node) {
		if (node) {
			node->size = getSize(node->left) + getSize(node->right) + 1;
		}
	}
	
	AVLNode* findMin(AVLNode* node) {
		if (node) {
			while (node->left) {
				node = node->left;
			}
		}
		return node;
	}

	AVLNode* findMax(AVLNode* node) {
		if (node) {
			while (node->right) {
				node = node->right;
			}
		}
		return node;
	}
	void eraseTree(AVLNode* node) {
		if (node) {
			eraseTree(node->left);
			eraseTree(node->right);
			delete node;
		}
	}
	std::function<int(const T&, const T&)> compareFunction_;
	AVLNode* root_;
};

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        if (nums.empty()) return 0;
        vector<long long> sum;
        sum.push_back(0);
        for (auto& n : nums) {
            sum.push_back(sum.back() + n);
        }
        AVLTree<long long> tree;
        int result = 0;
        for (int i = sum.size() - 1; i >= 0; --i) {
            long long a = sum[i];
            long long b1 = a + lower;
            long long b2 = a + upper;
            auto begin = tree.lowerBoundNode(b1);
            auto end = tree.upperBoundNode(b2);
            int size = tree.findSizeInBetween(begin, end);
            if (end != NULL && size > 0) {
                size--;
            }
            result += size;
            tree.insert(a);
        }
        return result;
    }
};


class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        if (nums.empty()) return 0;
        vector<long long> sum;
        sum.push_back(0);
        for (auto& n : nums) {
            sum.push_back(sum.back() + n);
        }
        int result = 0;
        vector<long long> help(sum.size());
        mergeSort(sum, 0, sum.size() - 1, result, help, lower, upper);
        return result;
    }
    
    void mergeSort(vector<long long>& s, int begin, int end, int& result, vector<long long>& helper, int lower, int upper) {
        if (begin >= end) {
            return;
        }
        int mid = (begin + end) / 2;
        mergeSort(s, begin, mid, result, helper, lower, upper);
        mergeSort(s, mid + 1, end, result, helper, lower, upper);
        int j = mid + 1;
        int k = mid + 1;
        /*
        printf("s[%d-%d] = ", begin, mid);
        for (int i = begin; i <= mid; ++i) {
            printf("%d ", s[i]);
        }
        printf("\n");
        printf("s[%d-%d] = ", mid + 1, end);
        for (int i = mid + 1; i <= end; ++i) {
            printf("%d ", s[i]);
        }
        printf("\n");
        */
        for (int i = begin; i <= mid; ++i) {
            while (j <= end && s[j] < lower + s[i]) {
                j++;
            }
            while (k <= end && s[k] <= upper + s[i]) {
                k++;
            }
            //printf("i = %d, s[i] = %d, j = %d, k = %d\n", i, s[i], j, k);
            result += k - j;
        }
        int i = begin;
        j = mid + 1;
        k = begin;
        while (i <= mid || j <= end) {
            if (i > mid) {
                helper[k++] = s[j++];
            } else if (j > end) {
                helper[k++] = s[i++];
            } else if (s[i] < s[j]) {
                helper[k++] = s[i++];
            } else {
                helper[k++] = s[j++];
            }
        }
        for (int i = begin; i <= end; ++i) {
            s[i] = helper[i];
        }
    }
};
