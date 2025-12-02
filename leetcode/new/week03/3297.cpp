// sliding window, no error
// 3297. Count Substrings That Can Be Rearranged to Contain a String I
class Solution {
   public:
    long long validSubstringCount(string word1, string word2) {
        unordered_map<char, int> need_map;
        for (char c : word2) {
            need_map[c]++;
        }
        long long result = 0;
        int begin = 0;
        int end = -1;
        unordered_map<char, int> count_map;
        size_t fulfill_count = 0;
        while (end + 1 < (int)word1.size()) {
            while (end + 1 < (int)word1.size() && fulfill_count < need_map.size()) {
                int c = word1[++end];
                count_map[c]++;
                if (auto p = need_map.find(c); p != need_map.end()) {
                    if (p->second == count_map[c]) {
                        fulfill_count++;
                    }
                }
            }
            while (begin <= end && fulfill_count == need_map.size()) {
                result += word1.size() - end;
                int c = word1[begin++];
                count_map[c]--;
                if (auto p = need_map.find(c); p != need_map.end()) {
                    if (p->second == count_map[c] + 1) {
                        fulfill_count--;
                    }
                }
            }
        }
        return result;
    }
};