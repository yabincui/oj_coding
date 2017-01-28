// 403. Frog Jump
class Solution {
public:
    unordered_map<int, bool> cache;
    int start, end;
    unordered_set<int> stone_set;
    bool canCross(vector<int>& stones) {
        cache.clear();
        start = stones[0];
        end = stones.back();
        stone_set.clear();
        stone_set.insert(stones.begin(), stones.end());
        return canJump(start, 1);
    }
    
    bool canJump(int from, int jump) {
        if (cache.find((from << 16) | jump) != cache.end()) {
            return false;
        }
        int to = from + jump;
        if (stone_set.find(to) == stone_set.end()) {
            return false;
        }
        if (to == end) {
            return true;
        }
        for (int nj = jump -1; nj <= jump + 1; nj++) {
            if (nj <= 0) {
                continue;
            }
            if (canJump(to, nj)) {
                return true;
            }
        }
        cache[(from << 16) | jump] = false;
        return false;
    }
};
