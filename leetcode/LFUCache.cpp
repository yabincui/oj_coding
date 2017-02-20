// 490. LFU Cache
class LFUCache {
    
    struct NodeHead;
    struct Node {
        NodeHead* head;
        Node* prev;
        Node* next;
        int key;
        int value;
    };
    
    struct NodeHead {
        NodeHead* prev;
        NodeHead* next;
        int freq;
        int node_count;
        Node node_list;
    };

    unordered_map<int, Node*> map;
    int capacity;
    NodeHead head_list;
    
    void addFreq(Node* node) {
        if (node->head->node_count == 1 && node->head != &head_list && node->head->next->freq != node->head->freq + 1) {
            // move entire NodeHead.
            node->head->freq++;
            return;
        }
        // remove node from NodeHead.
        
        if (node->head->next->freq != node->head->freq + 1) {
            //Create a new NodeHead.
            NodeHead* nhead = new NodeHead;
            nhead->prev = node->head;
            nhead->next = node->head->next;
            nhead->prev->next = nhead;
            nhead->next->prev = nhead;
        
            nhead->freq = node->head->freq + 1;
            nhead->node_count = 0;
            nhead->node_list.prev = &nhead->node_list;
            nhead->node_list.next = &nhead->node_list;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        
        NodeHead* old_head = node->head;
        NodeHead* nhead = node->head->next;
        node->head->node_count--;
        if (old_head->node_count == 0 && old_head != &head_list) {
            old_head->prev->next = old_head->next;
            old_head->next->prev = old_head->prev;
            delete old_head;
        }
        nhead->node_count++;
        node->head = nhead;
        node->prev = &nhead->node_list;
        node->next = nhead->node_list.next;
        node->prev->next = node;
        node->next->prev = node;
    }
    
    void addNodeToOneFreq(Node* node) {
        head_list.node_count++;
        node->head = &head_list;
        node->prev = &head_list.node_list;
        node->next = head_list.node_list.next;
        node->prev->next = node;
        node->next->prev = node;
    }
    
    void removeLFU() {
        //printf("removeLFU\n");
        //fflush(stdout);
        Node* node = NULL;
        if (head_list.node_count != 0) {
            //printf("head_list.node_count = %d\n", head_list.node_count);
            node = head_list.node_list.prev;
        } else if (head_list.next != &head_list) {
            node = head_list.next->node_list.prev;
        }
        if (node == NULL) return;
        //printf("remove key %d, freq %d\n", node->key, node->head->freq);
        //fflush(stdout);
        map.erase(node->key);
        node->prev->next = node->next;
        node->next->prev = node->prev;
        NodeHead* head = node->head;
        head->node_count--;
        if (head->node_count == 0 && head != &head_list) {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            delete head;
        }
        delete node;
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        head_list.prev = &head_list;
        head_list.next = &head_list;
        head_list.freq = 1;
        head_list.node_count = 0;
        head_list.node_list.prev = &head_list.node_list;
        head_list.node_list.next = &head_list.node_list;
    }
    
    int get(int key) {
        //printf("get %d\n", key);
        auto it = map.find(key);
        if (it == map.end()) {
            return -1;
        }
        addFreq(it->second);
        return it->second->value;
    }
    
    void put(int key, int value) {
        //printf("put %d %d\n", key, value);
        auto it = map.find(key);
        //printf("find %d\n", key);
        if (it != map.end()) {
            //printf("t1\n");
            it->second->value = value;
            addFreq(it->second);
            return;
        }
        //printf("t2, capacity = %d, map.size() %d\n", capacity, (int)map.size());
        if (map.size() == capacity) {
            //printf("before removeLFU\n");
            removeLFU();
        }
        if (map.size() < capacity) {
            Node* node = new Node;
            node->key = key;
            node->value = value;
            addNodeToOneFreq(node);
            map[key] = node;
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
