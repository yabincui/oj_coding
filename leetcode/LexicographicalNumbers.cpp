// 386. Lexicographical Numbers.
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> result;
        for (int i = 1; i <= 9; ++i) {
            recur(i, n, result);
        }
        return result;
    }
    
    void recur(int cur, int n, vector<int>& result) {
        //printf("recur cur = %d, n = %d\n", cur, n);
        if (cur > n) {
            return;
        }
        result.push_back(cur);
        cur *= 10;
        for (int i = 0; i <= 9; ++i) {
            recur(cur + i, n, result);
        }
    }
};
