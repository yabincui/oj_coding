// 440 Kth Smallest in Lexicographical Order
class Solution {
public:

    vector<int> vals;
    uint64_t count[11];
    uint64_t sum_count[11];
    int res;
    int n;
    
    int findKthNumber(int n, int k) {
        k--;
        res = 1;
        while (k != 0) {
            int count = 0;
            for (uint64_t first = res, second = res + 1; first <= n; first *= 10, second *= 10) {
                count += min(second, (uint64_t)(n + 1)) - first;
            }
            if (k < count) {
                k--;
                res *= 10;
            } else {
                k -= count;
                res++;
            }
        }
        return res;
    }

    int findKthNumber1(int n, int k) {
        count[0] = 1;
        sum_count[0] = 1;
        for (int i = 1; i <= 10; ++i) {
            count[i] = count[i-1] * 10;
            sum_count[i] = sum_count[i-1] + count[i];
        }
        vals.clear();
        this->n = n;
        while (n != 0) {
            vals.push_back(n % 10);
            n /= 10;
        }
        k--;
        res = 0;
        findEqual(vals.size(), k);
        return res;
    }
    
    void findStrictSmaller(int digits, int& k) {
        //printf("findStrictSmaller(%d, %d)\n", digits, k);
        while (k != 0) {
            k--;
            int cur_digit = k / sum_count[digits-1];
            k -= cur_digit * sum_count[digits-1];
            res = res * 10 + cur_digit;
            findStrictSmaller(digits-1, k);
            digits--;
        }
    }

    void findEqual(int digits, int& k) {
        //printf("findEqual(%d, %d)\n", digits, k);
        int start = 1;
        while (start == 1 || k != 0) {
            if (!start) {
                k--;
            }
            digits--;
            int mid = vals[digits];
            int cur_digit = k / sum_count[digits] + start;
            if (cur_digit < mid) {
                k -= (cur_digit - start) * sum_count[digits];
                res = res * 10 + cur_digit;
                findStrictSmaller(digits, k);
                break;
            }
            k -= (mid - start) * sum_count[digits];
            start = 0;
            int tmp = n % count[digits] + 1;
            if (digits >= 1) {
                tmp += sum_count[digits - 1];
            }
            //printf("k = %d, tmp = %d\n", k, tmp);
            if (k < tmp) {
                res = res * 10 + mid;
                continue;
            }
            k -= tmp;
            cur_digit = k / sum_count[digits-1] + mid + 1;
            k -= (cur_digit - mid - 1) * sum_count[digits-1];
            res = res * 10 + cur_digit;
            findStrictSmaller(digits-1, k);
            break;
        }
    }
};
