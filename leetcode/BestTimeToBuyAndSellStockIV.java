public class BestTimeToBuyAndSellStockIV {
  public int maxProfit(int k, int[] prices) {
    int m = prices.length;
    int n = Math.min(k * 2, m);
    if (m == 0) {
      return 0;
    }
    if (n == m) {
      return maxProfit2(prices);
    }
    System.out.printf("m = %d, n = %d\n", m, n);
    // dp[i][j] is in day i, finish transaction j, the best benefit.
    // The price in day i is prices[i - 1], the transaction j means buy j/2 + j%2 times, and sell j/2 times.
    int[][] dp = new int[m + 1][n + 1];
    dp[0][0] = 0;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n && j <= i; ++j) {
        if (j % 2 == 1) {
          // we buy at this time.
          dp[i][j] = dp[i - 1][j - 1] - prices[i - 1];
          if (i - 1 >= j) {
            dp[i][j] = Math.max(dp[i][j], dp[i - 1][j]);
          }
        } else {
          // we sell at this time.
          dp[i][j] = dp[i - 1][j - 1] + prices[i - 1];
          if (i - 1 >= j) {
            dp[i][j] = Math.max(dp[i][j], dp[i - 1][j]);
          }
        }
      }
    }
    int result = 0;
    for (int j = 0; j <= n; ++j) {
      result = Math.max(result, dp[m][j]);
    }
    return result;
  }

  public int maxProfit2(int[] prices) {
    int n = prices.length;
    // dp[0] hold no stock, dp[1] hold one stock.
    int[][] dp = new int[n][2];
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i < n; ++i) {
      dp[i][0] = Math.max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
      dp[i][1] = Math.max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }
    return dp[n - 1][0];
  }
}
