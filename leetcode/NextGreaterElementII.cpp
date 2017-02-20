// 503. Next Greater Element II
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> res(nums.size(), -1);
        stack<pair<int, int>> st;
        for (int i = 0; i < nums.size() * 2; ++i) {
            int pos = i % nums.size();
            while (!st.empty() && st.top().second < nums[pos]) {
                res[st.top().first] = nums[pos];
                st.pop();
            }
            if (!st.empty() && st.top().first == pos) {
                break;
            }
            st.push(make_pair(pos, nums[pos]));
        }
        return res;
    }
};
