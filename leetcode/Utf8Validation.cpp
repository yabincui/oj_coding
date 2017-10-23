// 393. UTF-8 Validation
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int n = data.size();
        int* p = data.data();
        while (n > 0) {
            int used;
            //printf("n = %d\n", n);
            if (!getUtf8(p, n, &used)) {
                return false;
            }
            p += used;
            n -= used;
        }
        return true;
    }
    
    bool getUtf8(int* data, int n, int* used_count) {
        if (n == 0) {
            return false;
        }
        int follow_count = 0;
        for (int i = 7; i >= 0; --i) {
            if ((data[0] >> i) & 1) {
                follow_count++;
            } else {
                break;
            }
        }
        if (follow_count == 1) {
            return false;
        }
        if (follow_count > 0) {
            follow_count--;
        }
        //printf("follow_count = %d, n = %d\n", follow_count, n);
        if (follow_count >= 4) {
            return false;
        }
        if (n < follow_count + 1) {
            return false;
        }
        for (int i = 1; i <= follow_count; ++i) {
            if ((data[i] & 0xc0) != 0x80) {
                return false;
            }
        }
        *used_count = follow_count + 1;
        return true;
    }
};
