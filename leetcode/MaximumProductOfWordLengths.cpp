class Solution {
    
    int* dp;
    
public:
    
    Solution() {
        dp = new int[1 << 26];
    }
    
    ~Solution() {
        delete [] dp;
    }
    
    int maxProduct(vector<string>& words) {
        auto comp = [](const string& s1, const string& s2) {
            return s1.size() > s2.size();
        };
        sort(words.begin(), words.end(), comp);
        vector<int> bitcode;
        for (int i = 0; i < words.size(); ++i) {
            int bits = 0;
            for (char c : words[i]) {
                bits |= 1 << (c - 'a');
            }
            bitcode.push_back(bits);
        }
        int res = 0;
        for (int i = 0; i < words.size(); ++i) {
            if (words[i].empty()) break;
            int min_len = res / words[i].size();
            for (int j = i + 1; j < words.size(); ++j) {
                if (words[j].size() <= min_len) break;
                if ((bitcode[i] & bitcode[j]) == 0) {
                    res = max(res, (int)(words[i].size() * words[j].size()));
                    break;
                }
            }
        }
        return res;
        
    }
    
    int maxProductTL(vector<string>& words) {
        int mask = (1 << 26) - 1;
        memset(dp, 0, (mask + 1) * sizeof(int));
        for (auto& s : words) {
            int bits = 0;
            for (char c : s) {
                bits |= 1 << (c - 'a');
            }
            dp[bits] = max(dp[bits], (int)s.size());
        }
        for (int i = 1; i <= mask; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (i & (1 << j)) {
                    dp[i] = max(dp[i], dp[i & ~(1 << j)]);
                }
            }
        }
        int res = 0;
        for (int i = 1; i <= mask; ++i) {
            res = max(res, dp[i] * dp[mask & ~i]);
        }
        return res;
    }
};