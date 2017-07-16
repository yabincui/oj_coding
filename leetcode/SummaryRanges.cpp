class Solution {
    
    string getRange(int start, int end) {
        char s[40];
        if (start == end) {
            sprintf(s, "%d", start);
        } else {
            sprintf(s, "%d->%d", start, end);
        }
        return s;
    }
    
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        if (nums.empty()) return res;
        int start, end;
        for (int i = 0; i < nums.size(); ++i) {
            if (i == 0) {
                start = end = nums[0];
            } else if (end + 1 == nums[i]) {
                end++;
            } else {
                res.push_back(getRange(start, end));
                start = end = nums[i];
            }
        }
        res.push_back(getRange(start, end));
        return res;
    }
};
