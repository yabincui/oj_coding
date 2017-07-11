class Solution {
    
    void calcOne(vector<char>& op_stack, vector<int>& val_stack) {
        int b = val_stack.back(); val_stack.pop_back();
        int a = val_stack.back(); val_stack.pop_back();
        char c = op_stack.back(); op_stack.pop_back();
        if (c == '+') {
            a += b;
        } else if (c == '-') {
            a -= b;
        } else if (c == '*') {
            a *= b;
        } else if (c == '/') {
            a /= b;
        }
        val_stack.push_back(a);
    }
    
public:
    int calculate(string s) {
        vector<int> val_stack;
        vector<char> op_stack;
        const char *p = s.c_str();
        while (*p != '\0') {
            //printf("*p = %c\n", *p);
            if (isspace(*p)) {
                p++;
            } else if (isdigit(*p)) {
                int val = 0;
                while (isdigit(*p)) {
                    val = val * 10 + *p - '0';
                    p++;
                }
                val_stack.push_back(val);
            } else if (*p == '+' || *p == '-') {
                while (!op_stack.empty()) {
                    calcOne(op_stack, val_stack);
                }
                op_stack.push_back(*p++);
            } else if (*p == '*' || *p == '/') {
                while (!op_stack.empty() && (op_stack.back() == '*' || op_stack.back() == '/')) {
                    calcOne(op_stack, val_stack);
                }
                op_stack.push_back(*p++);
            }
        }
        while (!op_stack.empty()) {
            calcOne(op_stack, val_stack);
        }
        return val_stack[0];
    }
};
