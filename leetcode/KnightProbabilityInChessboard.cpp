class Solution {
    
    void erase(vector<vector<double>>& dp) {
        for (auto& s : dp) {
            for (auto& value : s) {
                value = 0;
            }
        }
    }
    
    double dr[8] = {1, 1, 2, 2, -1, -1, -2, -2};
    double dc[8] = {2, -2, 1, -1, 2, -2, 1, -1};
    
public:
    double knightProbability(int N, int K, int r, int c) {
        vector<vector<double>> dp(N, vector<double>(N, 0));
        vector<vector<double>> ndp(N, vector<double>(N, 0));
        
        dp[r][c] = 1.0;
        for (int i = 0; i < K; ++i) {
            for (int r = 0; r < N; ++r) {
                for (int c = 0; c < N; ++c) {
                    if (dp[r][c] > 0) {
                        double prob = dp[r][c] / 8.0;
                        for (int d = 0; d < 8; ++d) {
                            int nr = r + dr[d];
                            int nc = c + dc[d];
                            if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
                                continue;
                            }
                            ndp[nr][nc] += prob;
                        }
                    }
                }
            }
            dp = ndp;
            erase(ndp);
        }
        double sum = 0;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                sum += dp[r][c];
            }
        }
        return sum;
    }
};
