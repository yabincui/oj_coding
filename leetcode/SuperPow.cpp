class Solution {
    
    int mul(int a, int b) {
        return (a * b) % 1337;
    }
    
public:
    int superPow(int a, vector<int>& b) {
        int res = 1;
        int x = mul(a, 1);
        for (int i = b.size() - 1; i >= 0; --i) {
            int s[11];
            s[0] = 1;
            for (int j = 1; j <= 10; ++j) {
                s[j] = mul(s[j-1], x);
            }
            res = mul(res, s[b[i]]);
            x = s[10];
        }
        return res;
    }
};