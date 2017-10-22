class RangeModule {
    
    vector<pair<int, int>> ranges;
    
public:
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        vector<pair<int, int>> next;
        bool has_wait_p = true;
        pair<int, int> wait_p = make_pair(left, right);
        for (auto& p : ranges) {
            if (p.second < left) {
                next.push_back(p);
            } else if (p.first > right) {
                if (has_wait_p) {
                    has_wait_p = false;
                    next.push_back(wait_p);
                }
                next.push_back(p);
            } else {
                // intersect with wait_p.
                wait_p.first = min(wait_p.first, p.first);
                wait_p.second = max(wait_p.second, p.second);
            }
        }
        if (has_wait_p) {
            next.push_back(wait_p);
        }
        ranges = next;
        //printf("after add(%d, %d)\n", left, right);
        //printRange();
        
    }
    
    bool queryRange(int left, int right) {
        auto it = upper_bound(ranges.begin(), ranges.end(), make_pair(left, INT_MAX));
        if (it != ranges.begin()) {
            --it;
            //printf("it->second = %d\n", it->second);
            return it->second >= right;
        }
        return false;
    }
    
    void removeRange(int left, int right) {
        vector<pair<int, int>> next;
        for (auto& p : ranges) {
            if (p.second < left) {
                next.push_back(p);
            } else if (p.first > right) {
                next.push_back(p);
            } else {
                if (p.first < left) {
                    pair<int, int> tmp = make_pair(p.first, left);
                    next.push_back(tmp);
                }
                if (p.second > right) {
                    next.push_back(make_pair(right, p.second));
                }
            }
        }
        ranges = next;
        //printf("after remove (%d, %d)\n", left, right);
        //printRange();
        
    }
    
    void printRange() {
        for (int i = 0; i < ranges.size(); ++i) {
            printf("ranges[%d] = %d, %d\n", i, ranges[i].first, ranges[i].second);
        }
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule obj = new RangeModule();
 * obj.addRange(left,right);
 * bool param_2 = obj.queryRange(left,right);
 * obj.removeRange(left,right);
 */