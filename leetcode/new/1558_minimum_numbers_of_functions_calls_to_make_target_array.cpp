// key: bit operation
class Solution {
public:
    int minOperations(vector<int>& nums) {
        // To get a value, how many +1, how many *2.
        // A B
        // 2^m + 2^n + 2^k. not biggest. 2 boost
        // 0b110 (+1, *2 (10), +1(11), *2(110)). max shift 2 + how many 1s.
        // [1, 5] => 1, 101 3+2=5
        int ops = 0;
        int max_shift = 0;
        for (int value : nums) {
            int shift = 0;
            while (value != 0) {
                if ((value & 1) == 1) {
                    ops++;
                }
                shift++;
                value >>= 1;
            }
            shift--;
            max_shift = max(max_shift, shift);
        }
        return max_shift + ops;
    }
};