class Solution {
    
    struct Trie {
        bool isword;
        unordered_map<int, Trie*> child;
        
        Trie() : isword(false) {
        }
        
        ~Trie() {
            //printf("delete Trie\n");
            for (auto& pair : child) {
                delete pair.second;
            }
        }
        
        void addWord(const string& s) {
            Trie* cur = this;
            for (auto c : s) {
                int id = c - 'a';
                if (cur->child.find(id) == cur->child.end()) {
                    cur->child[id] = new Trie;
                }
                cur = cur->child[id];
            }
            cur->isword = true;
        }
    };
    
    static bool compareLength(const string& s1, const string& s2) {
        return s1.size() < s2.size();
    }
    
    Trie* root;
    vector<bool>* dp;
    const string* word;
    
    bool formable(const string& word, Trie& root) {
        //printf("formable %s\n", word.c_str());
        vector<bool> dp(word.size() + 1, false);
        dp[0] = true;
        this->root = &root;
        this->dp = &dp;
        this->word = &word;
        dfs(0, &root);
        //printf("formable %s = %d\n", word.c_str(), (int)dp[word.size()]);
        return dp[word.size()];
    }
    
    void dfs(int word_id, Trie* cur) {
    start:
        //printf("dfs(word = %s, word_id = %d, cur = %p, root = %p\n", word.c_str(), word_id, cur, root);
        if (!cur) return;
        if (cur->isword) {
            if ((*dp)[word_id]) return;
            //printf("word %s, dp[%d] = true\n", word.c_str(), word_id);
            (*dp)[word_id] = true;
            //printf("back to root");
            dfs(word_id, root);
            if ((*dp)[word->size()]) return;
        }
        if (word_id == word->size()) return;
        //printf("goto char %c\n", word[word_id]);
        auto it = cur->child.find((*word)[word_id] - 'a');
        if (it != cur->child.end()) {
            cur = it->second;
            word_id++;
            goto start;
        }
    }
    
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        // 1. sort strings by length
        // 2. use dp to check if current word is formable.
        // 3. use trie to store visited trees.
        sort(words.begin(), words.end(), compareLength);
        Trie root;
        vector<string> result;
        for (auto& word : words) {
            if (word.empty()) continue;
            if (formable(word, root)) {
                result.push_back(word);
            } else {
                root.addWord(word);
            }
        }
        return result;
    }
};
