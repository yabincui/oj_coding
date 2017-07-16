class Solution {
    
    struct Node {
        int sum;
        double average;
        int len;
    };
    
    struct Range {
        int sum;
        double average;
        int len;
    };
    
    int n;
    vector<int> nums;
    int k;
    vector<int> sum_array;
    vector<int> root; // if root[i] > 0, it refers to its parent, if root[i] < 0, it is root, and -root[i] is the size of the union set.
    double average_limit;
    
    bool combine(int a, int b) {
        if (root[a] >= 0 || root[b] >= 0) {
            return false;
        }
        int end = b - root[b] - 1;
        double sum = sum_array[end + 1] - sum_array[a];
        if (sum / (end - a + 1) >= average_limit) {
            root[b] = a;
            root[a] = -(end + 1 - a);
            //printf("combine %d, %d\n", a, b);
            return true;
        }
        return false;
    }
    
    bool combine(int a, int b, int c) {
        if (root[a] >= 0 || root[b] >= 0 || root[c] >= 0) {
            return false;
        }
        int end = c - root[c] - 1;
        double sum = sum_array[end + 1] - sum_array[a];
        if (sum / (end - a + 1) >= average_limit) {
            root[b] = root[c] = a;
            root[a] = -(end + 1 - a);
            //printf("combine %d, %d, %d\n", a, b, c);
            return true;
        }
        return false;
    }
    
    int findRoot(int a) {
        int r = a;
        while (root[r] >= 0) {
            r = root[r];
        }
        int t = a;
        while (root[t] >= 0) {
            int next = root[t];
            root[t] = r;
            t = next;
        }
        return r;
    }
    
    void tryCombine2(int cur_pos) {
        queue<pair<int, bool>> q;
        q.push(make_pair(cur_pos, true));
        
        while (!q.empty()) {
            auto pair = q.front(); q.pop();
            int cur = pair.first;
            if (root[cur] >= 0) {
                continue;
            }
            int prev_root = -1;
            int next_root = -1;
            if (cur > 0) {
                prev_root = findRoot(cur - 1);
                if (combine(prev_root, cur)) {
                    q.push(make_pair(prev_root, true));
                }
            }
            if (cur - root[cur] < n) {
                next_root = findRoot(cur - root[cur]);
                if (combine(cur, next_root)) {
                    q.push(make_pair(cur, true));
                }
            }
            if (prev_root != -1 && next_root != -1) {
                if (combine(prev_root, cur, next_root)) {
                    q.push(make_pair(prev_root, true));
                }
            }
            if (pair.second) {
                if (prev_root != -1) {
                    q.push(make_pair(prev_root, false));
                }
                if (next_root != -1) {
                    q.push(make_pair(next_root, false));
                }
            }
        }
    }
    
    bool ok(double average) {
        average_limit = average;
        //printf("average_limit = %f\n", average_limit);
        memset(root.data(), -1, sizeof(int) * n);
        
        for (int i = 0; i < n; ++i) {
            if (root[i] < 0) {
                tryCombine2(i);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (root[i] <= -k) {
                double sum = sum_array[i - root[i]] - sum_array[i];
                double avg = sum / (-root[i]);
                //printf("sum = %f, root[%d] = %d\n", sum, i, root[i]);
                //printf("i = %d, avg = %f, average_limit = %f\n", i, avg, average_limit);
                if (avg >= average_limit) {
                    //printf("average %f, ok, from %d\n", average, i);
                    return true;
                }
            }
        }
        //printf("average %f, not ok\n", average);
        return false;
    }
    
    bool averageOk(double avg, vector<int>& nums, int k, vector<int>& sums) {
        double kneed = avg * k;
        double max_support = 0;
        for (int i = nums.size() - 1; i >= 0; --i) {
            double ksum = sums[i+1] - sums[i-k+1];
            if (ksum + max_support >= kneed) {
                return true;
            }
            max_support = max(0.0, max_support + nums[i] - avg);
        }
        return false;
    }
    
public:
    double findMaxAverage(vector<int>& nums, int k) {
        vector<int> sum(nums.size() + 1);
        sum[0] = 0;
        for (int i = 1; i <= nums.size(); ++i) {
            sum[i] = sum[i-1] + nums[i-1];
        }
        double low = -10000;
        double high = 10000;
        while (high - low > 1e-6) {
            double mid = (low + high) / 2;
            if (averageOk(mid, nums, k, sum)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return (low + high) / 2;
    }


    double findMaxAverageSlow2(vector<int>& nums, int k) {
        int n = nums.size();
        int sum_array[n + 1];
        sum_array[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum_array[i] = sum_array[i-1] + nums[i-1];
        }
        int maxSumLen[n + 1];
        memcpy(maxSumLen, sum_array, sizeof(maxSumLen));

        for (int i = 1; i < n; ++i) {
            for (int j = i + k - 1; j < n; ++j) {
                int len = j - i + 1;
                maxSumLen[len] = max(maxSumLen[len], sum_array[j + 1] - sum_array[i]);
            }
        }
        double maxRes = (double)maxSumLen[k] / k;
        for (int i = k + 1; i <= n; ++i) {
            maxRes = max(maxRes, (double)maxSumLen[i] / i);
        }
        return maxRes;
    }
    
    double findMaxAverageSlow(vector<int>& nums, int k) {
        int n = nums.size();
        int sum_array[n + 1];
        sum_array[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum_array[i] = sum_array[i-1] + nums[i-1];
        }
        bool hasMaxRes = false;
        double maxRes;
        for (int i = 0; i < n; ++i) {
            for (int j = i + k - 1; j < n; ++j) {
                double sum = sum_array[j + 1] - sum_array[i];
                double avg = sum / (j - i + 1);
                if (!hasMaxRes) {
                    hasMaxRes = true;
                    maxRes = avg;
                } else {
                    maxRes = max(maxRes, avg);
                }
            }
        }
        return maxRes;
    }
    
    double findMaxAverageWrongWay2(vector<int>& nums, int k) {
        this->n = nums.size();
        this->k = k;
        this->nums = nums;
        sum_array.resize(n + 1);
        sum_array[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum_array[i] = sum_array[i-1] + nums[i-1];
        }
        root.resize(n);
        
        double low = -10000;
        double high = 10000;
        
        
        while (high - low > 1e-6) {
            double mid = (low + high) / 2;
            if (ok(mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return (high + low) / 2;
    }
    
    double findMaxAverageWrongWay(vector<int>& nums, int k) {
        int n = nums.size();
        vector<Node> dp(n);  // dp[i] is the max average value starting from i.
        dp[n-1].sum = nums[n-1];
        dp[n-1].average = nums[n-1];
        dp[n-1].len = 1;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] > dp[i+1].average) {
                dp[i].sum = dp[i].average = nums[i];
                dp[i].len = 1;
            } else {
                dp[i].sum = dp[i+1].sum + nums[i];
                dp[i].len = dp[i+1].len + 1;
                dp[i].average = (double)dp[i].sum / dp[i].len;
            }
        }
        double res = 0;
        int sum_of_k_minus_one = 0;
        for (int i = 0; i < n; ++i) {
            if (i >= k - 1) {
                double sum = sum_of_k_minus_one + dp[i].sum;
                double average = sum / (dp[i].len + k - 1);
                if (i == k - 1) {
                    res = average;
                } else {
                    res = max(res, average);
                }
            }
            sum_of_k_minus_one += nums[i];
            if (i >= k - 1) {
                sum_of_k_minus_one -= nums[i - k + 1];
            }
        }
        return res;
    }
};
