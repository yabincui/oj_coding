class Solution {
    
    vector<int> origin;
    vector<int> order;
    
    void moveToNextOrder() {
        // 1 2 3
        // 1 3 2
        // 2 1 3
        // 2 3 1
        // 3 1 2
        
        if (order.empty()) return;
        for (int i = order.size() - 2; i >= 0; --i) {
            if (order[i] < order[i + 1]) {
                // 1 2 3 4 5 9 8 7 6
                // 1 2 3 4 6 5 7 8 9
                
                reverse(order.begin() + i + 1, order.end());
                auto it = lower_bound(order.begin() + i + 1, order.end(), order[i]);
                swap(order[i], *it);
                return;
            }
        }
        // 9 8 7 6 5 4 3 2 1
        reverse(order.begin(), order.end());
    }
    
public:
    Solution(vector<int> nums) {
        origin = nums;
        for (int i = 0; i < nums.size(); ++i) {
            order.push_back(i);
        }
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return origin;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> res;
        for (int i = 0; i < order.size(); ++i) {
            res.push_back(origin[order[i]]);
        }
        moveToNextOrder();
        return res;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */