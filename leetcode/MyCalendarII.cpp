class MyCalendarTwo {
    
    vector<pair<int, int>> save_v;  // first is time, second is is_start.
    
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        if (start >= end) return false;
        vector<pair<int, int>> v = save_v;
        v.push_back(make_pair(start, 1));
        v.push_back(make_pair(end, 0));
        sort(v.begin(), v.end());
        int count = 0;
        for (auto& p : v) {
            if (p.second == 1) {
                count++;
                if (count == 3) {
                    return false;
                }
            } else {
                count--;
            }
        }
        save_v = v;
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo obj = new MyCalendarTwo();
 * bool param_1 = obj.book(start,end);
 */
