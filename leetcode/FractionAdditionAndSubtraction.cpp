class Solution {
    
    struct Number {
        int64_t numerator;
        int64_t denominator;
        
        Number(int64_t numerator = 0, int64_t denominator = 1) : numerator(numerator), denominator(denominator) {}
        
        void add(Number& o) {
            int64_t base = denominator * o.denominator;
            int64_t up = numerator * o.denominator + o.numerator * denominator;
            int64_t factor = gcd(base, up);
            numerator = up / factor;
            denominator = base / factor;
        }

        int64_t gcd(int64_t a, int64_t b) {
            if (a < 0) a = -a;
            if (b < 0) b = -b;
            if (a < b) {
                swap(a, b);
            }
            int64_t c;
            while (b != 0) {
                c = a % b;
                a = b;
                b = c;
            }
            return a;
        }
    };
    
    bool getNum(string& s, int& i, int64_t* value) {
        *value = 0;
        int flag = 1;
        if (i == s.size()) return false;
        if (s[i] == '-' || s[i] == '+') {
            flag = s[i] == '-' ? -1 : 1;
            i++;
        }
        if (i == s.size() || !isdigit(s[i])) {
            return false;
        }
        while (i < s.size() && isdigit(s[i])) {
            *value = *value * 10 + s[i] - '0';
            i++;
        }
        if (flag == -1) {
            *value = -*value;
        }
        return true;
    }
    
    vector<Number> getNums(string& s) {
        vector<Number> nums;
        int i = 0;
        while (i < s.size()) {
            int64_t up, base;
            if (!getNum(s, i, &up)) {
                break;
            }
            if (s[i] != '/') {
                break;
            }
            i++;
            if (!getNum(s, i, &base)) {
                break;
            }
            nums.push_back(Number(up, base));
        }
        return nums;
    }
    
public:
    string fractionAddition(string expression) {
        vector<Number> nums = getNums(expression);
        if (nums.empty()) return "";
        for (int i = 1; i < nums.size(); ++i) {
            nums[0].add(nums[i]);
        }
        char s[100];
        snprintf(s, sizeof(s), "%lld/%lld", (long long)nums[0].numerator, (long long)nums[0].denominator);
        return s;
    }
};