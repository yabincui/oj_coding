// 336. Palindrome Pairs
class Solution {
private:
    struct Node {
      vector<int> pos;
      Node* child[26];
      
      Node() {
          memset(child, 0, sizeof(child));
      }
    };
    
    void insertNode(Node*& root, const char* s, int size, int pos) {
        Node** pp = &root;
        int i = 0;
        while (*pp != NULL && i < size) {
            pp = &(*pp)->child[s[i] - 'a'];
            //printf("s[%d] = %c, pp = %p\n", i, s[i], *pp);
            i++;
        }
        for (; i < size; ++i) {
            *pp = new Node;
            pp = &(*pp)->child[s[i]-'a'];
            //printf("s[%d] = %c, pp = %p\n", i, s[i], *pp);
        }
        if (*pp == NULL) {
            *pp = new Node;
            //printf("new pp %p\n", *pp);
        }
        (*pp)->pos.push_back(pos);
    }
    
    void freeNode(Node* root) {
        if (root != NULL) {
            for (int i = 0; i < 26; ++i) {
                freeNode(root->child[i]);
            }
            delete root;
        }
    }
    
    void search(Node* root, const char* path, int size, int pos, unordered_set<uint64_t>& hit_map) {
        for (int i = size - 1; i >= 0; --i) {
            root = root->child[path[i] - 'a'];
            if (root == NULL) {
                //printf("break at i = %d\n", i);
                return;
            }
        }
        if (root == NULL) {
            //printf("break at last pos\n");
            return;
        }
        if (root->pos.empty()) {
            //printf("no points here\n");
        }
        for (auto n : root->pos) {
            //printf("add pair (%d, %d)\n", pos, n);
            if (n == pos) continue;
            uint64_t key = ((uint64_t)pos << 32) | n;
            hit_map.insert(key);
        }
    }
    
    bool isPalindrome(string& s, int start, int end) {
        if (start >= end) {
            return true;
        }
        while (start < end) {
            if (s[start] != s[end]) {
                return false;
            }
            start++;
            end--;
        }
        return true;
    }
    
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
       Node* root = NULL;
       Node* completeRoot = NULL;
       for (int i = 0; i < words.size(); ++i) {
           for (int omit_size = 0; omit_size <= words[i].size(); ++omit_size) {
               if (isPalindrome(words[i], 0, omit_size - 1)) {
                   //printf("insertNode, pos %d, s = %s\n", i, words[i].c_str() + omit_size);
                   insertNode(root, words[i].c_str() + omit_size, words[i].size() - omit_size, i);
               }
               //printf("insert complete Node, pos %d, s = %s\n", i, words[i].c_str());
               insertNode(completeRoot, words[i].c_str(), words[i].size(), i);
           }
       }
       vector<vector<int>> res;
       unordered_set<uint64_t> hit_set;
       for (int i = 0; i < words.size(); ++i) {
           for (int omit_size = 1; omit_size <= words[i].size(); ++omit_size) {
               if (isPalindrome(words[i], words[i].size() - omit_size, words[i].size() - 1)) {
                   //printf("search i = %d, word %s\n", i, words[i].substr(0, words[i].size() - omit_size).c_str());
                   search(completeRoot, words[i].c_str(), words[i].size() - omit_size, i, hit_set);
               }
           }
           search(root, words[i].c_str(), words[i].size(), i, hit_set);
       }
       freeNode(root);
       freeNode(completeRoot);
       for (uint64_t key : hit_set) {
           int p1 = key >> 32;
           int p2 = key & 0xffffffff;
           res.push_back({p1, p2});
       }
       return res;
    }
};
