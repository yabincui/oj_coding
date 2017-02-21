// 432. All Oone Data Structure
class AllOne {
private:
    struct Node {
        string key;
        int val;
        Node* prev, *next;
        
        Node() {
            prev = this;
            next = this;
        }
        
        void addAfter(Node* p) {
            prev = p;
            next = p->next;
            prev->next = this;
            next->prev = this;
        }
        
        void addBefore(Node* p) {
            next = p;
            prev = p->prev;
            prev->next = this;
            next->prev = this;
        }
        
        void rmFromList() {
            prev->next = next;
            next->prev = prev;
        }
    };
    
    Node head;
    unordered_map<string, Node*> key_map;
    unordered_map<int, pair<Node*, Node*>> value_map;
    
    void addToValueMap(Node* node, bool first) {
        auto it = value_map.find(node->val);
        if (it == value_map.end()) {
            value_map[node->val] = make_pair(node, node);
        } else if (first) {
            value_map[node->val].first = node;
        } else {
            value_map[node->val].second = node;
        }
    }
    
    void rmFromValueMap(Node* node) {
        bool change_head = false;
        bool change_tail = false;
        if (node->prev == &head || node->prev->val != node->val) {
            change_head = true;
        }
        if (node->next == &head || node->next->val != node->val) {
            change_tail = true;
        }
        if (change_head && change_tail) {
            value_map.erase(node->val);
        } else if (change_head) {
            value_map[node->val].first = node->next;
        } else if (change_tail) {
            value_map[node->val].second = node->prev;
        }
    }
    
    void addNode(Node* node) {
        node->val = 1;
        node->addBefore(&head);
        addToValueMap(node, false);
    }
    
    void rmNode(Node* node) {
        rmFromValueMap(node);
        node->rmFromList();
    }
    
    void incNode(Node* node) {
        Node* head = value_map[node->val].first->prev;
        rmFromValueMap(node);
        node->val++;
        addToValueMap(node, false);
        node->rmFromList();
        node->addAfter(head);
    }
    
    void decNode(Node* node) {
        Node* head = value_map[node->val].second->next;
        rmFromValueMap(node);
        node->val--;
        addToValueMap(node, true);
        node->rmFromList();
        node->addBefore(head);
    }
    
    void printState() {
        printf("list: ");
        for (Node* p = head.next; p != &head; p = p->next) {
            printf("-> (%s, %d) ", p->key.c_str(), p->val);
        }
        for (auto it = value_map.begin(); it != value_map.end(); ++it) {
            printf("value_map[%d] = (%s, %s)\n", it->first, it->second.first->key.c_str(), it->second.second->key.c_str());
        }
    }
    
    
public:
    /** Initialize your data structure here. */
    AllOne() {
        
    }
    
    ~AllOne() {
        Node* p = head.next;
        while (p != &head) {
            Node* n = p->next;
            delete p;
            p = n;
        }
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        //printf("inc key = %s\n", key.c_str());
        auto it = key_map.find(key);
        if (it == key_map.end()) {
            Node* node = new Node;
            node->key = key;
            node->val = 1;
            addNode(node);
            key_map[key] = node;
        } else {
            Node* node = it->second;
            incNode(node);
        }
        //printState();
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        //printf("dec key %s\n", key.c_str());
        auto it = key_map.find(key);
        if (it != key_map.end()) {
            Node* node = it->second;
            if (node->val == 1) {
                rmNode(node);
                key_map.erase(key);
            } else {
                decNode(node);
            }
        }
        //printState();
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (head.next == &head) {
            return "";
        }
        return head.next->key;
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (head.prev == &head) {
            return "";
        }
        return head.prev->key;
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */
