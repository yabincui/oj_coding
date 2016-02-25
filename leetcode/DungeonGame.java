public class DungeonGame {
  public int calculateMinimumHP(int[][] dungeon) {
    int m = dungeon.length;
    int n = dungeon[0].length;
    // dp[i][j] means the minimum hp should have when entering room (i, j) to achieve the bottom right.
    long[][] dp = new long[m][n];
    dp[m-1][n-1] = Math.max(1, 1-(long)dungeon[m-1][n-1]);
    for (int j = n - 2; j >= 0; --j) {
      dp[m-1][j] = Math.max(1, dp[m-1][j+1] - dungeon[m-1][j]);
    }
    for (int i = m - 2; i >= 0; --i) {
      dp[i][n-1] = Math.max(1, dp[i+1][n-1] - dungeon[i][n-1]);
      for (int j = n - 2; j >= 0; --j) {
        long v1 = Math.max(1, dp[i+1][j] - dungeon[i][j]);
        long v2 = Math.max(1, dp[i][j+1] - dungeon[i][j]);
        dp[i][j] = Math.min(v1, v2);
      }
    }
    return (int)dp[0][0];
  }
}
