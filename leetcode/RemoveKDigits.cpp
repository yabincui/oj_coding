// 402. Remove K Digits
class Solution {
public:
    string removeKdigits(string num, int k) {
        if (k >= num.size()) {
            return "0";
        }
        // find the cut place to cut the max 0 digits.
        int max_cut_digits = 0;
        int max_cut_pos = 0;
        int max_cut_use_k = 0;
        int use_k = 0;
        int cut_digits = 0;
        for (int i = 0; i < num.size() && use_k < k;) {
            if (num[i] - '0' != 0) {
                // remove it.
                use_k++;
                i++;
                while (i < num.size() && num[i] == '0') {
                    cut_digits++;
                    i++;
                }
                if (cut_digits > max_cut_digits) {
                    max_cut_digits = cut_digits;
                    max_cut_pos = i;
                    max_cut_use_k = use_k;
                }
            }
        }
        k -= max_cut_use_k;
        int start = max_cut_pos;
        if (k == 0) {
            if (start == num.size()) {
                return "0";
            }
            return num.substr(start);
        }
        //printf("k = %d, start = %d\n", k, start);
        string result;
        int digits[10];
        memset(digits, 0, sizeof(digits));
        int j = start;
        for (int i = start; i + k < num.size(); ++i) {
            while (j <= i + k && j < num.size()) {
                digits[num[j] - '0']++;
                //printf("add digit %d, j = %d\n", num[j] - '0', j);
                j++;
            }
            int sel_digit = 10;
            for (int t = 0; t <= 9; ++t) {
                if (digits[t] != 0) {
                    sel_digit = t;
                    break;
                }
            }
            //printf("i = %d, j=%d, sel_digit = %d, k = %d\n", i, j, sel_digit, k);
            while (num[i] != sel_digit + '0') {
                digits[num[i]-'0']--;
                //printf("rm digit %d, i = %d\n", num[i] - '0', i);
                i++;
                k--;
            }
            digits[num[i] - '0']--;
            //printf("rm digit %d, i = %d\n", num[i] - '0', i);
            result.push_back(num[i]);
        }
        if (result.empty()) {
            result = "0";
        }
        return result;
    }
};
