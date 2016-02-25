import java.util.*;

public class PerfectSquares {
  public int numSquares(int n) {
    int[] dp = new int[n + 1];
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
      int limit = (int)Math.sqrt(i);
      int min = Integer.MAX_VALUE;
      for (int j = 1; j <= limit; ++j) {
        int cur = dp[i - j * j] + 1;
        min = Math.min(min, cur);
      }
      dp[i] = min;
    }
    return dp[n];
  }
}
