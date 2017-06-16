class Solution {
    
    static bool compareInt(int a, int b) {
        return a > b;
    }
    
    typedef bool (*compareType)(int, int);
    
public:
    int thirdMax(vector<int>& nums) {
        priority_queue<int, vector<int>, compareType> q(compareInt);
        unordered_set<int> hit_set;
        for (auto& n : nums) {
            if (hit_set.find(n) != hit_set.end()) {
                continue;
            }
            hit_set.insert(n);
            if (q.size() < 3 || q.top() < n) {
                q.push(n);
            }
            if (q.size() > 3) {
                q.pop();
            }
        }
        if (q.size() == 3) {
            return q.top();
        }
        while (q.size() > 1) {
            q.pop();
        }
        if (q.size() == 1) {
            return q.top();
        }
        return -1;
    }
};
