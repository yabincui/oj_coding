class Solution {
    unordered_map<int, int> cache;
    int min_res;
    
    int getMinSteps(int n) {
        auto it = cache.find(n);
        if (it != cache.end()) {
            return it->second;
        }
        int res = n;
        for (int i = (int)sqrt(n); i > 1; --i) {
            res = min(res, 1 + getMinSteps(n - i * i));
        }
        cache[n] = res;
        return res;
    }
    
public:
    int numSquares(int n) {
        int res = getMinSteps(n);
        return res;
    }
};
