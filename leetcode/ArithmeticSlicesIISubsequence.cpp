// 446. Arithmetic Slices II - Subsequence
class Solution {
    
    unordered_map<int64_t, vector<int>> place_map;
    unordered_map<int64_t, int> dp;

public:
    int numberOfArithmeticSlices(vector<int>& A) {
        place_map.clear();
        for (int i = 0; i < A.size(); ++i) {
            place_map[A[i]].push_back(i);
        }
        dp.clear();
        int res = 0;
        for (int i = 0; i < A.size(); ++i) {
            for (int j = i + 1; j < A.size(); ++j) {
                int64_t diff = (int64_t)A[j] - A[i];
                if (abs(diff) > INT_MAX) continue;
                int count = findCount(A, j, diff);
                res += count - 1;
            }
        }
        return res;
    }
    
    int findCount(vector<int>& A, int pos, int64_t diff) {
        auto key = ((int64_t)pos << 32) | (uint32_t)diff;
        auto it = dp.find(key);
        if (it != dp.end()) {
            return it->second;
        }
        int res = 1;
        int64_t next = (int64_t)A[pos] + diff;
        auto it2 = place_map.find(next);
        if (it2 != place_map.end()) {
            auto it = upper_bound(it2->second.begin(), it2->second.end(), pos);
            for (; it != it2->second.end(); ++it) {
                res += findCount(A, *it, diff);
            }
        }
        dp[key] = res;
        return res;
    }
};
