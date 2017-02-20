// 179. Largest Number
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> v;
        for (auto n : nums) {
            v.push_back(to_string(n));
        }
        sort(v.begin(), v.end(), compareS);
        string res;
        for (auto& s : v) {
            res += s;
        }
        if (res.empty() || res[0] == '0') {
            return "0";
        }
        return res;
    }
    
    static bool compareS(string& a, string& b) {
        for (int i = 0; i < a.size() + b.size(); ++i) {
            char c1 = (i < a.size()) ? a[i] : b[i - a.size()];
            char c2 = (i < b.size()) ? b[i] : a[i - b.size()];
            if (c1 != c2) {
                return c1 > c2;
            }
        }
        return false;
    }
};
