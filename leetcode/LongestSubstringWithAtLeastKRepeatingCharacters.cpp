// 395. Longest Substring with At Least K Repeating Characters
class Solution {
public:
    int k;
    int max_len;

    int longestSubstring(string s, int k) {
        int n = s.size();
        int sum[n+1][26];
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < s.size(); ++i) {
            for (int j = 0; j < 26; ++j) {
                sum[i+1][j] = sum[i][j];
            }
            sum[i+1][s[i]-'a']++;
        }
        max_len = 0;
        this->k = k;
        findLongest(sum, 1, n);
        return max_len;
    }
    
    void findLongest(int sum[][26], int start, int end) {
        //printf("find start = %d, end = %d\n", start, end);
        if (end - start + 1 <= max_len) {
            return;
        }
        int cut = getCutChar(sum, start, end);
        //printf("cut = %d\n", cut);
        if (cut == -1) {
            int len = end - start + 1;
            if (max_len < len) {
                max_len = len;
            }
            return;
        }
        //printf("findCutPos, cut = %d, start %d, end %d\n", cut, start, end);
        int pos = findCutPos(sum, cut, start, end);
        //printf("cut pos = %d\n", pos);
        findLongest(sum, start, pos - 1);
        findLongest(sum, pos + 1, end);
    }
    
    int getCutChar(int sum[][26], int start, int end) {
        for (int i = 0; i < 26; ++i) {
            int count = sum[end][i] - sum[start-1][i];
            if (count > 0 && count < k) {
                return i;
            }
        }
        return -1;
    }
    
    int findCutPos(int sum[][26], int cut, int start, int end) {
        int low = start;
        int high = end;
        //printf("start-> %d, end ->%d\n", sum[start][cut], sum[end][cut]);
        while (true) {
            int mid = (low + high) / 2;
            //printf("low = %d, high = %d, mid = %d -> %d\n", low, high, mid, sum[mid][cut]);
            if (sum[mid][cut] - sum[mid-1][cut] == 1) {
                return mid;
            }
            if (sum[mid][cut] == sum[start-1][cut]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
};
