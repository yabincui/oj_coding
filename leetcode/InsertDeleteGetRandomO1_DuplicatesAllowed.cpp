// 381. Insert Delete GetRandom O(1) - Duplicates allowed
class RandomizedCollection {
    struct Node {
        Node* next;
        int pos;
        int val;
    };
    
    unordered_map<int, Node*> node_map;
    vector<Node*> node_v;
    
    int getRand(int size) {
        unsigned val = 0;
        val = (rand() % 65536 << 16) | (rand() % 65536);
        return (int)(val % size);
    }
    
    void show() {
        printf("v[%zu] = ", node_v.size());
        for (int i = 0; i < node_v.size(); ++i) {
            printf("%d (pos %d, next %d)", node_v[i]->val, node_v[i]->pos, node_v[i]->next ? node_v[i]->next->pos : -1);
        }
        printf("\n");
    }

public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    ~RandomizedCollection() {
        for (Node* n : node_v) {
            delete n;
        }
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        //printf("insert %d\n", val);
        Node* n = new Node;
        n->next = NULL;
        n->pos = node_v.size();
        n->val = val;
        node_v.push_back(n);
        auto it = node_map.find(val);
        if (it != node_map.end()) {
            n->next = it->second->next;
            it->second->next = n;
            //show();
            return false;
        } else {
            node_map[val] = n;
            //printf("new %d in map\n", val);
        }
        //show();
        return true;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        //printf("remove val %d\n", val);
        auto it = node_map.find(val);
        if (it == node_map.end()) {
            return false;
        }
        Node* n = it->second;
        if (n->next != NULL) {
            it->second = n->next;
        } else {
            node_map.erase(it);
            //printf("remove %d in map\n", val);
        }
        if (n->pos != node_v.size() - 1) {
            node_v[n->pos] = node_v.back();
            node_v[n->pos]->pos = n->pos;
        }
        node_v.resize(node_v.size() - 1);
        delete n;
        //show();
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return node_v[getRand(node_v.size())]->val;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
