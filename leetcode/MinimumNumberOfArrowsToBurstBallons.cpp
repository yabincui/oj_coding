class Solution {
    
    struct Range {
        int start, end;
        
        Range(int start, int end) : start(start), end(end) {}
    };
    
    static bool compareRange(Range& r1, Range& r2) {
        return r1.end < r2.end;
    }
    
    
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        vector<Range> v;
        for (auto& p : points) {
            v.emplace_back(p.first, p.second);
        }
        sort(v.begin(), v.end(), compareRange);
        if (v.empty()) return 0;
        int result = 0;
        for (int i = 0; i < v.size(); ++i) {
            int x = v[i].end;
            while (i + 1 < v.size() && x >= v[i + 1].start) {
                i++;
            }
            result++;
        }
        return result;
    }
};
