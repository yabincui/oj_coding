class Solution {
    
    vector<int64_t> nigh_count_array; // nigh_count_array[i] = 1 * 10^i has how many numbers have 9.

    void init() {
        nigh_count_array.resize(12);
        nigh_count_array[0] = 0;
        int64_t ten_i = 10;
        int64_t nigh_i = 9;
        for (int i = 1; i <= 11; ++i) {
            nigh_count_array[i] = ten_i - nigh_i;
            ten_i *= 10;
            nigh_i *= 9;
            //printf("nigh_count_array[%d] = %lld\n", i, (long long)nigh_count_array[i]);
        }
    }
    
    int64_t getNighCount(string& s) {
        vector<int64_t> v;
        for (auto c : s) {
            v.push_back(c - '0');
        }
        int level = s.size() - 1;
        int64_t count = 0;
        for (int i = 0; i < s.size(); ++i, level--) {
            count += v[i] * nigh_count_array[level];
            if (v[i] == 9) {
                int64_t left = 0;
                for (int j = i + 1; j < s.size(); ++j) {
                    left = left * 10 + v[j];
                }
                count += left + 1;
                return count;
            }
        }
        return count;
    }
    
public:
    Solution() {
        init();
    }
    
    int newInteger(int n) {
        int64_t low = 1;
        int64_t high = INT_MAX;
        //int64_t count = getNighCount(to_string(111));
        //printf("count = %lld\n", (long long)count);
        while (true) {
            int64_t mid = (low + high) / 2;
            string s = to_string(mid);
            int64_t nigh_count = getNighCount(s);
            int64_t left = mid - nigh_count;
            if (left < n) {
                low = mid + 1;
            } else if (left > n) {
                high = mid - 1;
            } else {
                if (s.find('9') == -1) {
                    return mid;
                }
                high = mid - 1;
            }
        }
    }
};
