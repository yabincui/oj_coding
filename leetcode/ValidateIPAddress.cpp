class Solution {
    
    bool isIPv4(string& s) {
        const char* p = s.c_str();
        for (int i = 0; i < 4; ++i) {
            if (i != 0) {
                if (*p++ != '.') {
                    return false;
                }
            }
            if (!isdigit(*p) || (*p == '0' && isdigit(*(p+1)))) {
                return false;
            }
            int number = 0;
            while (isdigit(*p)) {
                number = number * 10 + *p - '0';
                p++;
                if (number > 255) {
                    return false;
                }
            }
        }
        return *p == '\0';
    }
    
    bool isIPv6(string& s) {
        const char* p = s.c_str();
        for (int i = 0; i < 8; ++i) {
            if (i != 0) {
                if (*p != ':') {
                    return false;
                }
                p++;
            }
            int digit_count = 0;
            while (*p != ':' && *p != '\0') {
                if (!(isdigit(*p) || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F'))) {
                    return false;
                }
                digit_count++;
                if (digit_count > 4) {
                    return false;
                }
                p++;
            }
            if (digit_count == 0) {
                return false;
            }
            
        }
        return *p == '\0';
    }
    
public:
    string validIPAddress(string IP) {
        if (isIPv4(IP)) {
            return "IPv4";
        }
        if (isIPv6(IP)) {
            return "IPv6";
        }
        return "Neither";
    }
};
