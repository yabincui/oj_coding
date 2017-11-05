class Solution {
    
    int findRoot(vector<int>& ids, int a) {
        int tmp = a;
        while (ids[tmp] != tmp) {
            tmp = ids[tmp];
        }
        int root = tmp;
        while (a != root) {
            tmp = ids[a];
            ids[a] = root;
            a = tmp;
        }
        return root;
    }
    
    void union_set(vector<int>& ids, int a, int b) {
        int ra = findRoot(ids, a);
        int rb = findRoot(ids, b);
        ids[ra] = rb;
    }
    
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        vector<int> ids(n);
        for (int i = 0; i < n; ++i) {
            ids[i] = i;
        }
        unordered_map<string, int> email_to_account;
        for (int t = 0; t < accounts.size(); ++t) {
            auto& account = accounts[t];
            for (int i = 1; i < account.size(); ++i) {
                string& email = account[i];
                auto it = email_to_account.find(email);
                if (it == email_to_account.end()) {
                    email_to_account[email] = t;
                } else {
                    union_set(ids, it->second, t);
                }
            }
        }
        unordered_map<int, int> root_to_pos;
        int tmp = 0;
        for (int i = 0; i < ids.size(); ++i) {
            if (i == ids[i]) {
                int pos = root_to_pos.size();
                root_to_pos[i] = pos;
                //printf("root_to_pos[%d] = %d\n", i, pos);
            }
        }
        vector<set<string>> emails(root_to_pos.size());
        for (int i = 0; i < n; ++i) {
            int root = findRoot(ids, i);
            //printf("root[%d] = %d\n", i, root);
            auto& set = emails[root_to_pos[root]];
            for (int j = 1; j < accounts[i].size(); ++j) {
                set.insert(accounts[i][j]);
            }
        }
        vector<vector<string>> res(emails.size());
        for (auto& pair : root_to_pos) {
            int root = pair.first;
            int pos = pair.second;
            res[pos].push_back(accounts[root][0]);
            for (auto& s : emails[pos]) {
                res[pos].push_back(s);
                //printf("res[%d].add %s\n", pos, s.c_str());
            }
        }
        return res;
    }
};
