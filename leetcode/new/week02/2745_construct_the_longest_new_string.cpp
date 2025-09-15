// key: dp
// error: left an edge case for reasoning next step.
class Solution {
public:
    int longestString(int x, int y, int z) {
        // AA, BB, AB
        // AA => BB
        // BB => AA, AB
        // AB => AA, AB
        // max length. 50x50x50, last is A or B.
        // 50, 6 bit for x, 6 bit for y, 6 bit for z, 2 bit for prefix.
        unordered_map<int, int> cache;
        int result = 0;
        for (int prefix = 0; prefix <= 2; prefix++) {
            result = max(result, dfs(x, y, z, prefix, cache));
        }
        return result;
    }

    int dfs(int x, int y, int z, int prefix, unordered_map<int, int>& cache) {
        int key = to_key(x, y, z, prefix);
        if (auto it = cache.find(key); it != cache.end()) {
            return it->second;
        }
        int result = 0;
        if (prefix == 0) {
            // prefix is AA, can use BB
            if (y != 0) {
                result = 2 + dfs(x, y - 1, z, 1, cache);
            }
        } else if (prefix == 1) {
            // prefix is BB, can use AA or AB
            if (x != 0) {
                result = max(result, 2 + dfs(x - 1, y, z, 0, cache));
            }
            if (z != 0) {
                result = max(result, 2 + dfs(x, y, z - 1, 2, cache));
            }
        } else if (prefix == 2) {
            // prefix is AB, can use AA or AB
            if (x != 0) {
                result = max(result, 2 + dfs(x - 1, y, z, 0, cache));
            }
            if (z != 0) {
                result = max(result, 2 + dfs(x, y, z - 1, 2, cache));
            }
        }
        cache[key] = result;
        return result;
    }

    int to_key(int x, int y, int z, int prefix) {
        return x | (y << 6) | (z << 12) | (prefix << 18);
    }

    void from_key(int key, int& x, int& y, int& z, int& prefix) {
        x = key & 0x3f;
        key >>= 6;
        y = key & 0x3f;
        key >>= 6;
        z = key & 0x3f;
        key >>= 6;
        prefix = key & 0x3;
    }
};