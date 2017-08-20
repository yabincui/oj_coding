/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
    
public:
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        if (intervals.empty()) return 0;
        auto compareInterval = [](const Interval& i1, const Interval& i2) {
            return i1.end < i2.end;
        };
        sort(intervals.begin(), intervals.end(), compareInterval);
        int eraseCount = 0;
        int lastTime = intervals[0].start;
        for (auto& i : intervals) {
            if (lastTime > i.start) {
                eraseCount++;
            } else {
                lastTime = i.end;
            }
        }
        return eraseCount;
    }
};
