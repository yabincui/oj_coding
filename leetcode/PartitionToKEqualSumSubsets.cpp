#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;


class Solution {

    int getAverage(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) {
            return -1;
        }
        return sum / k;
    }

    bool recur(vector<int>& nums, int pos, vector<int>& slot, int average) {
        if (pos == nums.size()) {
            return true;
        }
        int add = nums[pos];
        for (int i = 0; i < slot.size(); ++i) {
            if (slot[i] + add <= average) {
                slot[i] += add;
                if (recur(nums, pos + 1, slot, average)) {
                    return true;
                }
                slot[i] -= add;
            }
        }
        return false;
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int average = getAverage(nums, k);
        if (average == -1) return false;
        sort(nums.begin(), nums.end());
        reverse(nums.begin(), nums.end());
        if (nums[0] > average) {
            return false;
        }
        vector<int> slot(k, 0);
        if (recur(nums, 0, slot, average)) {
            return true;
        }
        return false;
    }

    bool canPartitionKSubsets2(vector<int>& nums, int k) {
        int sum0=accumulate(nums.begin(),nums.end(),0);
        if(sum0%k) return 0;
        //discrete knapsack without repetition

        int n=nums.size();
        vector<vector<int>> value(sum0/k+1,vector<int>(n+1));
        for(int i=1;i<=n;i++)
        {
            int wi=nums[i-1];
            //cout<<wi<<endl;
            for(int w=1;w<=sum0/k;w++) //all smaller problems
            {
                value[w][i]=value[w][i-1];//if w>wi then it use previous value
                if(w>=wi)
                {
                    value[w][i]=max(value[w-wi][i-1]+wi,value[w][i-1]);                    
                }
            }
         }
        return value[sum0/k][n]==sum0/k;
    }
};

void randomInput(vector<int>& nums, int& k) {
    int n = random() % 16 + 1;
    nums.resize(n);
    k = random() % n + 1;
    int average = random() % 10000 + 1;
    int sum = average * n;
    for (int i = 0; i < n; ++i) {
        int value = sum - (n - i - 1);
        if (i < n - 1) {
            value = random() % value + 1;
        }
        nums[i] = value;
        sum -= value;
    }
}

int main() {
    Solution s;
    for (int i = 0; i < 100; ++i) {
        vector<int> nums;
        int k;
        randomInput(nums, k);
        bool res = s.canPartitionKSubsets(nums, k);
        bool res2 = s.canPartitionKSubsets2(nums, k);
        printf("nums = ");
        for (int i = 0; i < nums.size(); ++i) {
            printf("%d, ", nums[i]);
        }
        printf(", k = %d, res = %d, res2 = %d\n", k, res, res2);
        if (res != res2) break;
    }
    return 0;
}


