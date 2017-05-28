class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        vector<bool> visited(nums.size(), false);
        int max_size = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (visited[i]) {
                continue;
            }
            int size = 0;
            int cur = i;
            while (!visited[cur]) {
                size++;
                visited[cur] = true;
                cur = nums[cur];
            }
            max_size = max(max_size, size);
        }
        return max_size;
    }
};
