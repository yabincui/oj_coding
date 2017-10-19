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
    vector<int> findRightInterval(vector<Interval>& intervals) {
        map<int, int> hit_map;
        for (int i = 0; i < intervals.size(); ++i) {
            hit_map[intervals[i].start] = i;
        }
        vector<int> result(intervals.size());
        for (int i = 0; i < result.size(); ++i) {
            auto it = hit_map.lower_bound(intervals[i].end);
            if (it == hit_map.end()) {
                result[i] = -1;
            } else {
                result[i] = it->second;
            }
        }
        return result;
    }
};