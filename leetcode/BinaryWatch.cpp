// 401. Binary Watch
class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> result;
        char buf[40];
        for (int i = 0; i < 1024; ++i) {
            if (getBits(i) == num) {
                int hour = i >> 6;
                int minute = i & 0x3f;
                if (hour >= 12 || minute >= 60) {
                    continue;
                }
                snprintf(buf, sizeof(buf), "%d:%02d", hour, minute);
                result.push_back(buf);
            }
        }
        return result;
    }
    
    int getBits(int n) {
        int count = 0;
        while (n != 0) {
            count++;
            n &= (n - 1);
        }
        return count;
    }
};
