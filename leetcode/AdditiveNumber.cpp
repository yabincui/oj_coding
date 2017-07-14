class Solution {
    
    struct Node {
        int start;
        int end;
        Node(int start = 0, int end = 0) : start(start), end(end) {}
    };
    
    void addSum(Node a, Node b, string& num, string& sum) {
        sum.clear();
        int add = 0;
        for (int i = a.end, j = b.end; i >= a.start || j >= b.start || add != 0; --i, --j) {
            if (i >= a.start) add += num[i] - '0';
            if (j >= b.start) add += num[j] - '0';
            sum.push_back(add % 10 + '0');
            add /= 10;
        }
    }
    
    bool checkSum(string& num, Node a, string& sum) {
        for (int i = 0, j = a.end; i < sum.size() && j >= a.start; ++i, --j) {
            if (sum[i] != num[j]) return false;
        }
        return true;
    }
    
    bool validRange(Node& a, string& num) {
        if (a.end != a.start) {
            return num[a.start] != '0';
        }
        return true;
    }
    
    bool check(Node a, Node b, string& num) {
        if (!validRange(a, num) || !validRange(b, num)) return false;
        
        string sum;
        while (b.end != num.size() - 1) {
            addSum(a, b, num, sum);
            //printf("sum = %s\n", sum.c_str());
            int start = b.end + 1;
            if (start + sum.size() > num.size()) {
                return false;
            }
            Node c(start, start + sum.size() - 1);
            if (!validRange(c, num)) return false;
            if (!checkSum(num, c, sum)) {
                return false;
            }
            a = b;
            b = c;
        }
        return true;
    }
    
public:
    bool isAdditiveNumber(string num) {
        int n = num.size();
        for (int len1 = 1; len1 <= n / 2; ++len1) {
            for (int len2 = 1; n - len2 - len1 >= max(len1, len2); ++len2) {
                Node a(0, len1 - 1);
                Node b(len1, len1 + len2 - 1);
                if (check(a, b, num)) {
                    return true;
                }
            }
        }
        return false;
    }
};
