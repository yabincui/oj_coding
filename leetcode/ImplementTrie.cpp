// 208. Implement Trie
class Trie {
private:
    struct Node {
        bool is_word;
        Node* children[26];
    
        Node() {
            is_word = false;
            memset(children, 0, sizeof(children));
        }
    };

    Node* root;
    
    void freeNode(Node* p) {
        if (p == NULL)
            return;
        for (int i = 0; i < 26; ++i) {
            freeNode(p->children[i]);
        }
        delete p;
    }
    
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new Node;
    }
    
    ~Trie() {
        freeNode(root);
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* p = root;
        for (auto& c : word) {
            if (p->children[c - 'a'] == NULL) {
                p->children[c - 'a'] = new Node;
            }
            p = p->children[c - 'a'];
        }
        p->is_word = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* p = root;
        for (auto& c : word) {
            p = p->children[c - 'a'];
            if (p == NULL) {
                return false;
            }
        }
        return p->is_word;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node* p = root;
        for (auto& c : prefix) {
            p = p->children[c - 'a'];
            if (p == NULL) {
                return false;
            }
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */
