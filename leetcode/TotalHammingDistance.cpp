class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size();
        int count[32][2];
        memset(count, 0, sizeof(count));
        for (auto value : nums) {
            for (int i = 0; i < 32; ++i) {
                count[i][value & 1]++;
                value >>= 1;
            }
        }
        int total = 0;
        for (int i = 0; i < 32; ++i) {
            total += count[i][0] * count[i][1];
        }
        return total;
    }
};
