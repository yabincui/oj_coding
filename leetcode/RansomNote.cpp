// 383. Ransom Note
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int map[256];
        memset(map, 0, sizeof(map));
        for (auto& c : ransomNote) {
            map[c]++;
        }
        for (auto& c : magazine) {
            if (map[c] > 0) {
                map[c]--;
            }
        }
        for (int i = 0; i < 256; ++i) {
            if (map[i] != 0) {
                return false;
            }
        }
        return true;
    }
};
