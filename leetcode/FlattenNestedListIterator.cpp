/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
private:

    struct Node {
        NestedInteger* value;  
        int index;
        
        Node(NestedInteger* value, int index) : value(value), index(index) {}
    };
    
    vector<Node> stack;
    vector<NestedInteger> nestedList;
    int global_index;
    
    void moveNext() {
        while (!stackHasValue()) {
            if (stack.empty()) {
                if (global_index == nestedList.size()) {
                    break;
                }
                pushStackValue(&nestedList[global_index++]);
            } else {
                int id = stack.back().index;
                NestedInteger* value = stack.back().value;
                if (id == value->getList().size()) {
                    stack.pop_back();
                } else {
                    stack.back().index++;
                    pushStackValue(&value->getList()[id]);
                }
            }
        }
    }
    
    void pushStackValue(NestedInteger* value) {
        while (value != NULL) {
            if (value->isInteger()) {
                stack.push_back(Node(value, 0));
                return;
            }
            if (value->getList().empty()) {
                return;
            }
            stack.push_back(Node(value, 1));
            value = &(value->getList()[0]);
        }
    }
    
    bool stackHasValue() {
        return !stack.empty() && stack.back().value->isInteger();
    }
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        global_index = 0;
        this->nestedList = nestedList;
    }

    int next() {
        if (!hasNext()) {
            return -1;
        }
        int value = stack.back().value->getInteger();
        stack.pop_back();
        return value;
    }

    bool hasNext() {
        if (stackHasValue()) {
            return true;
        }
        moveNext();
        return stackHasValue();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
