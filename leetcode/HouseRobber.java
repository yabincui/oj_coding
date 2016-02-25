public class HouseRobber {
  public int rob(int[] nums) {
    // dp[i] the max value achieved by 0..i-1 houses.
    int[] dp = new int[nums.length + 1];
    for (int i = 1; i <= nums.length; ++i) {
      if (i >= 2) {
        dp[i] = Math.max(dp[i-1], nums[i-1] + dp[i-2]);
      } else {
        dp[i] = Math.max(dp[i-1], nums[i-1]);
      }
    }
    return dp[nums.length];
  }
}
