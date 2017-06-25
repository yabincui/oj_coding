class Solution {
    
    int map[1002001];
    int MOD = 1000000007;
    
    // s[n][k] = s[n-1][k] + s[n-1][k-1] + ... + s[n-1][k-n+1];
    // s[n][k-1] = s[n-1][k-1] + s[n-1][k-2] + ... + s[n-1][k-n];
    // s[n][k] - s[n][k-1] = s[n-1][k] - s[n-1][k-n];
    int find(int n, int k) {
        if (k < 0) {
            return 0;
        }
        if (k == 0) {
            return 1;
        }
        if (n <= 1) {
            return 0;
        }
        
        int max_pair = (n - 1) * n / 2;
        if (k > max_pair) {
            return 0;
        }
        if (k == max_pair) {
            return 1;
        }
        
        if (k == 1) {
            return n - 1;
        }
        int key = n * 1001 + k;
        if (map[key] != -1) {
            return map[key];
        }
        int sum = find(n, k-1) + find(n - 1, k) - find(n - 1, k - n);
        if (sum < 0) {
            sum += MOD;
        } else if (sum >= MOD) {
            sum -= MOD;
        }
        if (sum < 0 || sum >= MOD) {
            printf("hello\n");
        }
        //printf("dp[%d][%d] = dp[%d][%d] + dp[%d][%d] - dp[%d][%d] = %d + %d - %d = %d\n",
        //    n, k, n, k - 1, n - 1, k, n - 1, k - n, find(n, k-1), find(n-1, k), find(n-1, k-n), sum);
        map[key] = sum;
        return sum;
    }
    
public:

    Solution() {
        memset(map, -1, sizeof(map));
    }

    int kInversePairs(int n, int k) {
        int res = find(n, k);
        return res;
    }
};
