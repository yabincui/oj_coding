// 458. Poor Pigs.
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        if (buckets <= 1) {
            return 0;
        }
        if (minutesToTest < minutesToDie) {
            return -1;
        }
        int round = minutesToTest / minutesToDie;
        if (round >= buckets) {
            return 1;
        }
        int base = round + 1;
        int t = 1;
        int pigs = 0;
        while (t < buckets) {
            t *= base;
            pigs++;
        }
        return pigs;
    }
};



