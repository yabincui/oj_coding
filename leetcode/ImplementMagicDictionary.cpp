class MagicDictionary {
    
    struct Node {
        bool isWord;
        Node* child[26];
        
        Node() {
            isWord = false;
            memset(child, 0, sizeof(child));
        }
        
        void addWord(string& s) {
            Node* cur = this;
            for (char c : s) {
                int i = c - 'a';
                if (cur->child[i] == nullptr) {
                    cur->child[i] = new Node;
                }
                cur = cur->child[i];
            }
            cur->isWord = true;
        }
        
        bool search(string& s) {
            char* p = &s[0];
            return search_r(p, false);
        }
        
        bool search_r(char* p, bool changed) {
            if (*p == '\0') {
                return isWord && changed;
            }
            
            Node* next = child[*p - 'a'];
            if (next && next->search_r(p + 1, changed)) {
                return true;
            }
            if (changed) return false;
            for (int i = 0; i < 26; ++i) {
                if (i == *p - 'a') {
                    continue;
                }
                next = child[i];
                if (next && next->search_r(p + 1, true)) {
                    return true;
                }
            }
            return false;
        }
    };
    
    Node root;
    
    
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for (auto& s : dict) {
            root.addWord(s);
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        return root.search(word);
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */
