// 496. Next Greater Element I
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        stack<int> st;
        unordered_map<int, int> hit_map;
        for (int i = 0; i < nums.size(); ++i) {
            int cur = nums[i];
            while (!st.empty() && st.top() < cur) {
                hit_map[st.top()] = cur;
                st.pop();
            }
            st.push(cur);
        }
        while (!st.empty()) {
            hit_map[st.top()] = -1;
            st.pop();
        }
        vector<int> res;
        for (int i = 0; i < findNums.size(); ++i) {
            res.push_back(hit_map[findNums[i]]);
        }
        return res;
    }
};
