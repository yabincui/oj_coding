class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        // n - i >= s[i], use s[i]
        for (int i = citations.size() - 1; i >= 0; --i) {
            if (citations.size() - i >= citations[i]) {
                return citations[i];
            } else {
                int t = citations.size() - i;
                int left = (i > 0 ? citations[i - 1] : 0);
                if (t >= left) {
                    return t;
                }
            }
        }
        return 0;
    }
};
