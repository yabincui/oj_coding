class Solution {
   
    int* dp;
    
    int needToKey(const vector<int>& needs) {
        int res = 0;
        for (auto need : needs) {
            res = res * 7 + need;
        }
        return res;
    }
    
    void keyToNeed(int key, vector<int>& needs) {
        for (int i = needs.size() - 1; i >= 0; --i) {
            needs[i] = key % 7;
            key /= 7;
        }
    }
    
    bool exceed(vector<int>& a, vector<int>& b) {
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] > b[i]) {
                return true;
            }
        }
        return false;
    }
    
    bool useSpecial(vector<int>& origin, vector<int>& special, vector<int>& tmp2, int* prev_key) {
        for (int i = 0; i < origin.size(); ++i) {
            tmp2[i] = origin[i] - special[i];
            if (tmp2[i] < 0) {
                return false;
            }
        }
        *prev_key = needToKey(tmp2);
        return true;
    }
    
public:
    
    Solution() {
        dp = new int[200000];
    }
    
    ~Solution() {
        delete [] dp;
    }
    
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        memset(dp, -1, sizeof(int) * 200000);
        dp[0] = 0;
        vector<int> tmp(needs.size());
        vector<int> tmp2(needs.size());
        int need_key = needToKey(needs);
        int prev_key;
        for (int key = 1; key <= need_key; key++) {
            keyToNeed(key, tmp);
            if (exceed(tmp, needs)) {
                continue;
            }
            for (int i = 0; i < special.size(); ++i) {
                if (useSpecial(tmp, special[i], tmp2, &prev_key)) {
                    int val = special[i].back() + dp[prev_key];
                    if (dp[key] == -1 || dp[key] > val) {
                        dp[key] = val;
                    }
                }
            }
            // buy all items.
            int val = 0;
            for (int i = 0; i < tmp.size(); ++i) {
                val += tmp[i] * price[i];
            }
            if (dp[key] == -1 || dp[key] > val) {
                dp[key] = val;
            }
        }
        return dp[need_key];
    }
};
