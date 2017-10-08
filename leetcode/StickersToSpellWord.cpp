class Solution {
    
    int dp[(1 << 15)];
    
    struct Node {
        int letters[26];
    };
    
    vector<Node> getLetters(vector<string>& stickers) {
        vector<Node> res(stickers.size());
        for (int i = 0; i < res.size(); ++i) {
            Node& node = res[i];
            memset(node.letters, 0, sizeof(node.letters));
            for (auto c : stickers[i]) {
                node.letters[c - 'a']++;
            }
        }
        return res;
    }
    
    int getPrevBits(Node& node, string& target, int bits) {
        int used[26];
        memset(used, 0, sizeof(used));
        int prev = 0;
        for (int i = 0; i < target.size(); i++) {
            int bit = 1 << i;
            if (bit & bits) {
                char c_id = target[i] - 'a';
                if (used[c_id] < node.letters[c_id]) {
                    used[c_id]++;
                } else {
                    prev |= bit;
                }
            }
        }
        return prev;
    }
    
public:
    int minStickers(vector<string>& stickers, string target) {
        int m = stickers.size();
        vector<Node> letters = getLetters(stickers);
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        int n = target.size();
        int mask = (1 << n) - 1;
        for (int i = 1; i <= mask; ++i) {
            int value = -1;
            for (int j = 0; j < stickers.size(); ++j) {
                int prev = getPrevBits(letters[j], target, i);
                if (prev == i || dp[prev] == -1) {
                    continue;
                }
                int temp = dp[prev] + 1;
                if (value == -1 || value > temp) {
                    value = temp;
                }
            }
            dp[i] = value;
        }
        return dp[mask];
    }
};
