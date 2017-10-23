class Solution {
    
    void insert(vector<int>& nums, int left, int right) {
        // 1 2 3
        // 1 3 2
        // 1 2 3 4
        // 1 3 2 4
        int a = left;
        int mid = left + (right - mid) / 2;
        int b = mid + 1;
        vector<int> tmp;
        while (a <= mid) {
            tmp.push_back(nums[a++]);
            if (b <= right) {
                tmp.push_back(nums[b++]);
            }
        }
        for (int i = left; i <= right; ++i) {
            nums[i] = tmp[i-left];
        }
    }
    
public:
    void wiggleSortWrong(vector<int>& nums) {
        // 1 2 3 3 3 3 4 5
        // 3 4 3 5 1 3 2 3
        sort(nums.begin(), nums.end());
        // cut half.
        // 1 2 3 3 3 4 5
        // 3 4 3 5 1 3 2
        if (nums.size() < 3) {
            return;
        }
        int left1 = 0;
        int left2 = nums.size() / 2;
        int right1 = left2 - 1;
        int right2 = nums.size() - 1;
        
        insert(nums, left1, right1);
        insert(nums, left2, right2);
        reverse(nums.begin() + left1, nums.begin() + right1 + 1);
        reverse(nums.begin() + left2, nums.begin() + right2 + 1);
        reverse(nums.begin(), nums.end());
        
        // 1 1 1 4 5 6
        // 1 6 1 5 1 4
    }
    
    void wiggleSort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        if (nums.size() < 3) {
            return;
        }
        vector<int> v;
        int middle = (nums.size() % 2 == 0) ? (nums.size() / 2 - 1) : (nums.size() / 2);
        int a = middle;
        int b = nums.size() - 1;
        while (a >= 0) {
            v.push_back(nums[a--]);
            if (b > middle) {
                v.push_back(nums[b--]);
            }
        }
        for (int i = 0; i < nums.size(); ++i) {
            nums[i] = v[i];
        }
    }
};