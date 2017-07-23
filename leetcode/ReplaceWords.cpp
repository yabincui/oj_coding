class Solution {
    
    struct Trie {
        bool isWord;
        Trie* child[26];
        
        Trie(bool isWord) : isWord(isWord) {
            memset(child, 0, sizeof(child));
        }
        
        void addWord(string& s) {
            Trie* cur = this;
            for (char c : s) {
                Trie* next = cur->child[c - 'a'];
                if (next == nullptr) {
                    next = cur->child[c - 'a'] = new Trie(false);
                }
                cur = next;
            }
            cur->isWord = true;
        }
        
        ~Trie() {
            for (int i = 0; i < 26; ++i) {
                if (child[i]) {
                    delete child[i];
                }
            }
        }
    };
    
    string findRoot(Trie& root, string& s) {
        Trie* cur = &root;
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            cur = cur->child[c - 'a'];
            if (cur == nullptr) {
                return s;
            }
            if (cur->isWord) {
                return s.substr(0, i + 1);
            }
        }
        return s;
    }

    
public:
    string replaceWords(vector<string>& dict, string sentence) {
        Trie root(false);
        for (auto& s : dict) {
            root.addWord(s);
        }
        string res;
        string curWord;
        for (auto c : sentence) {
            if (c >= 'a' && c <= 'z') {
                curWord.push_back(c);
            } else {
                if (!curWord.empty()) {
                    res += findRoot(root, curWord);
                    curWord.clear();
                }
                res.push_back(c);
            }
        }
        if (!curWord.empty()) {
            res += findRoot(root, curWord);
        }
        return res;
    }
};
