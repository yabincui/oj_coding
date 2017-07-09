class Solution {
    struct Node {
        int64_t xCount;
        int64_t addValue;
    };
    
    Node parseString(string s) {
        //printf("parseString %s\n", s.c_str());
        Node res;
        res.xCount = 0;
        res.addValue = 0;
        const char* p = s.c_str();
        int flag = 1;
        int t = 0;
        while (*p != '\0') {
            if (++t < 10) {
                //printf("*p = %c\n", *p);
            }
            if (*p == 'x') {
                res.xCount += flag;
                p++;
            } else if (*p == '+' || *p == '-') {
                flag = (*p == '+') ? 1 : -1;
                p++;
            } else if (isdigit(*p)) {
                int64_t val = 0;
                while (isdigit(*p)) {
                    val = val * 10 + *p - '0';
                    p++;
                }
                if (*p == 'x') {
                    res.xCount += flag * val;
                    p++;
                } else {
                    res.addValue += flag * val;
                }
            }
        }
        return res;
    }
    
    
public:
    string solveEquation(string equation) {
        string inf_ret = "Infinite solutions";
        string no_ret = "No solution";
        
        size_t split = equation.find('=');
        //fprintf(stderr, "split = %zu\n", split);
        if (split == string::npos) {
            return inf_ret;
        }
        Node leftNode = parseString(equation.substr(0, split));
        Node rightNode = parseString(equation.substr(split + 1));
        int64_t xCount = leftNode.xCount - rightNode.xCount;
        int64_t result = rightNode.addValue - leftNode.addValue;
        if (xCount == 0) {
            if (result == 0) {
                return inf_ret;
            }
            return no_ret;
        }
        char buf[40];
        result /= xCount;
        snprintf(buf, sizeof(buf), "x=%lld", (long long)result);
        return buf;
    }
};
