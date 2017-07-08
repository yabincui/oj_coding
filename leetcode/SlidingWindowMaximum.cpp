class Solution {
    
    struct Node {
        int pos;
        int value;
        Node(int pos, int value) : pos(pos), value(value) {}
    };
    
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // priority_queue O(nlogn)
        // map O(nlogk)
        // unordered_map + link_list (not work well)
        // stack or queue, this is the most likely to work in O(n)
        // stack with higher value, left to right, index increase, value decrease, if a increase, erase values before.
        deque<Node> dep;
        vector<int> result;
        for (int i = 0; i < nums.size(); ++i) {
            int value = nums[i];
            while (!dep.empty() && dep.back().value <= value) {
                dep.pop_back();
            }
            dep.emplace_back(i, value);
            if (dep.front().pos <= i - k) {
                dep.pop_front();
            }
            if (i >= k - 1) {
                result.push_back(dep.front().value); 
            }
        }
        return result;
    }
};
