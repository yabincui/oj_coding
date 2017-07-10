/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class SummaryRanges {
    
    std::map<int, int> map;
    
public:
    /** Initialize your data structure here. */
    SummaryRanges() {

    }
    
    void addNum(int val) {
        auto it = map.lower_bound(val);
        if (it == map.end()) {
            if (!map.empty()) {
                auto prev_it = it;
                prev_it--;
                if (prev_it->second >= val) {
                    return;
                } else if (prev_it->second == val - 1) {
                    prev_it->second = val;
                    return;
                }
            }
            map[val] = val;
        } else if (it == map.begin()) {
            if (it->first == val) {
                return;
            } else if (it->first == val + 1) {
                map[val] = it->second;
                map.erase(val + 1);
            } else {
                map[val] = val;
            }
        } else {
            auto prev_it = it;
            prev_it--;
            if (prev_it->second >= val || it->first == val) {
                return;
            } else if (prev_it->second == val - 1) {
                if (it->first == val + 1) {
                    prev_it->second = it->second;
                    map.erase(val + 1);
                } else {
                    prev_it->second = val;
                }
            } else if (it->first == val + 1) {
                map[val] = it->second;
                map.erase(val + 1);
            } else {
                map[val] = val;
            }
        }
    }
    
    vector<Interval> getIntervals() {
        vector<Interval> res;
        for (auto& pair : map) {
            res.emplace_back(pair.first, pair.second);
        }
        return res;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
