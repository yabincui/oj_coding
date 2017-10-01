class Solution {
    
    unordered_map<string, string> map;
    uint64_t id;
    
    string prefix;
    
    string getNextSid() {
        string sid(6, '0');
        int temp = id++;
        for (int i = 0; i < 6; ++i) {
            int value = temp % 62;
            char c;
            if (value < 10) {
                c = value + '0';
            } else if (value < 36) {
                c = value - 10 + 'a';
            } else {
                c = value - 36 + 'A';
            }
            sid[5 - i] = c;
            temp /= 62;
        }
        return sid;
    }
    
public:
    
    Solution() {
        prefix = "http://tinyurl.com/";
        id = 0;
    }

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string sid = getNextSid();
        map[sid] = longUrl;
        return prefix + sid;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        string sid = shortUrl.substr(prefix.size());
        return map[sid];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
