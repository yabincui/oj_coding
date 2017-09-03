class WordDictionary {
    
    struct Node {
        Node* child[26];
        bool isWord;
        
        Node() {
            memset(child, 0, sizeof(child));
            isWord = false;
        }
        
        ~Node() {
            for (int i = 0; i < 26; ++i) {
                if (child[i]) {
                    delete child[i];
                }
            }
        }
        
        void addWord(string& s) {
            Node* cur = this;
            for (char c : s) {
                int id = c - 'a';
                if (cur->child[id] == NULL) {
                    cur->child[id] = new Node;
                }
                cur = cur->child[id];
            }
            cur->isWord = true;
        }
        
        bool searchWord(string& s) {
            vector<Node*> q, nq;
            q.push_back(this);
            for (char c : s) {
                bool any = c == '.';
                int id = c - 'a';
                nq.clear();
                for (Node* cur : q) {
                    if (any) {
                        for (int i = 0; i < 26; ++i) {
                            if (cur->child[i]) {
                                nq.push_back(cur->child[i]);
                            }
                        }
                    } else {
                        if (cur->child[id]) {
                            nq.push_back(cur->child[id]);
                        }
                    }
                }
                q = std::move(nq);
                if (q.empty()) return false;
            }
            for (Node* cur : q) {
                if (cur->isWord) return true;
            }
            return false;
        }
    };
    
    Node root;
    
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        root.addWord(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return root.searchWord(word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */
