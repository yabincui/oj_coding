class MapSum {
    
    struct Trie {
        bool isWord;
        int nodeValue;
        int treeValue;
        Trie* child[26];
        
        Trie() {
            isWord = false;
            nodeValue = 0;
            treeValue = 0;
            memset(child, 0, sizeof(child));
        }
        
        void insert(string& s, int value) {
            Trie* cur = this;
            vector<Trie*> v;
            v.push_back(cur);
            for (char c : s) {
                if (c < 'a' || c > 'z') {
                    cur = nullptr;
                    break;
                }
                int id = c - 'a';
                if (cur->child[id] == nullptr) {
                    cur->child[id] = new Trie;
                }
                cur = cur->child[id];
                v.push_back(cur);
            }
            int changeValue;
            if (cur->isWord) {
                changeValue = value - cur->nodeValue;
            } else {
                changeValue = value;
            }
            cur->isWord = true;
            cur->nodeValue += changeValue;
            for (auto cur : v) {
                cur->treeValue += changeValue;
            }
        }
        
        int sum(string& s) {
            Trie* cur = this;
            for (char c : s) {
                int id = c - 'a';
                if (cur->child[id] == nullptr) {
                    return 0;
                }
                cur = cur->child[id];
            }
            return cur->treeValue;
        }
        
        ~Trie() {
            for (int i = 0; i < 26; ++i) {
                if (child[i]) {
                    delete child[i];
                }
            }
        }
    };
    
    Trie root;
    
public:
    /** Initialize your data structure here. */
    MapSum() {
        
    }
    
    
    void insert(string key, int val) {
        root.insert(key, val);
    }
    
    int sum(string prefix) {
        return root.sum(prefix);
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */
