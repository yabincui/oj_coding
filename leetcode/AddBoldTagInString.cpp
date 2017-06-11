class Solution {
    
    struct Trie {
        bool isWord;
        unordered_map<char, Trie*> children;
        Trie() {
            isWord = false;
        }
        
        void addWord(string& s) {
            Trie* cur = this;
            for (char c : s) {
                if (cur->children[c] == NULL) {
                    cur->children[c] = new Trie;
                }
                cur = cur->children[c];
            }
            cur->isWord = true;
        }
        
        Trie* getNext(char c) {
            auto it = children.find(c);
            if (it == children.end()) {
                return NULL;
            }
            return it->second;
        }
        
        ~Trie() {
            for (auto pair : children) {
                delete pair.second;
            }
        }
    };
    
    
    
public:
    string addBoldTag(string s, vector<string>& dict) {
        Trie root;
        for (string& str : dict) {
            root.addWord(str);
        }
        int n = s.size();
        vector<bool> inTag(n, false);
        for (int i = 0; i < n; ++i) {
            Trie* cur = &root;
            int end = -1;
            for (int j = i; j < n && cur != NULL; ++j) {
                cur = cur->getNext(s[j]);
                if (cur && cur->isWord) {
                    end = j;
                }
            }
            for (int j = i; j <= end; ++j) {
                inTag[j] = true;
            }
        }
        string res;
        bool inTagFlag = false;
        for (int i = 0; i < s.size(); ++i) {
            if (!inTagFlag && inTag[i]) {
                res += "<b>";
                inTagFlag = true;
            } else if (inTagFlag && !inTag[i]) {
                res += "</b>";
                inTagFlag = false;
            }
            res.push_back(s[i]);
        }
        if (inTagFlag) {
            res += "</b>";
        }
        return res;
    }
};


