#include <algorithm>
#include <vector>
using namespace std;
class Solution {
 public:
  int maxProfit(int k, vector<int>& prices) {
    int m = prices.size();
    if (k >= m) {
      return maxProfit2(k, prices);
    }
    int n = std::min(k * 2, m);
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n && j <= i; ++j) {
        if (j % 2 == 1) {
          // we buy at this time.
          dp[i][j] = dp[i - 1][j - 1] - prices[i - 1];
          if (i - 1 >= j) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
          }
        } else {
          // we sell at this time.
          dp[i][j] = dp[i - 1][j - 1] + prices[i - 1];
          if (i - 1 >= j) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
          }
        }
        printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
      }
    }
    int result = 0;
    for (int j = 0; j <= n; ++j) {
      result = max(result, dp[m][j]);
    }
    return result;
  }
  int maxProfit2(int k, vector<int>& prices) {
    int result = 0;
    for (size_t i = 1; i < prices.size(); ++i) {
      if (prices[i] > prices[i - 1]) {
        result += prices[i] - prices[i - 1];
      }
    }
    return result;
  }
};

int main() {
  Solution solution;
  vector<int> prices = {3,3,5,0,0,3,1,4};
  int result = solution.maxProfit(2, prices);
  printf("result = %d\n", result);
}
