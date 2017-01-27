// 397. Integer Replacement
class Solution {
public:
    unordered_map<int, int> cache;
    int integerReplacement(int n) {
        cache.clear();
        cache[1] = 0;
        return find(n);
    }
    int find(int n) {
        int count = 0;
        while ((n & 1) == 0) {
            n >>= 1;
            count++;
        }
        auto it = cache.find(n);
        if (it != cache.end()) {
            return count + it->second;
        }
        int a = find((n-1)/2+1) + 2;
        int b = find(n-1) + 1;
        if (a > b) {
            a = b;
        }
        cache[n] = a;
        return a + count;
    }
};
