// 394. Decode String
class Solution {
public:
    string decodeString(string s) {
        const char* p = s.c_str();
        return decodeString(p);
    }
    
    string decodeString(const char*& p) {
        string result;
        while (*p != '\0' && *p != ']') {
            if (isdigit(*p)) {
                int count = getInt(p);
                p++;
                string s = decodeString(p);
                for (int i = 0; i < count; ++i) {
                    result += s;
                }
            } else {
                result.push_back(*p++);
            }
        }
        if (*p == ']') {
            p++;
        }
        return result;
    }
    
    int getInt(const char*& p) {
        int value = 0;
        while (isdigit(*p)) {
            value = value * 10 + *p - '0';
            p++;
        }
        return value;
    }
    
};
