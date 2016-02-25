public class MaximumGap {
  public int maximumGap(int[] nums) {
    if (nums.length < 2) {
      return 0;
    }
    int min = nums[0];
    int max = nums[0];
    for (int i = 1; i < nums.length; ++i) {
      min = Math.min(min, nums[i]);
      max = Math.max(max, nums[i]);
    }
    if (min == max) {
      return 0;
    }
    int averageGap = (max - min) / (nums.length - 1);
    int[][] groups = new int[nums.length][2];
    boolean[] groupValid = new boolean[nums.length];
    for (int i = 0; i < nums.length; ++i) {
      int groupId = (nums[i] - min) / (averageGap + 1);
      if (groupValid[groupId] == false || groups[groupId][0] > nums[i]) {
        groups[groupId][0] = nums[i];
      }
      if (groupValid[groupId] == false || groups[groupId][1] < nums[i]) {
        groups[groupId][1] = nums[i];
      }
      groupValid[groupId] = true;
    }
    int maxDiff = averageGap;
    int prevValue = groups[0][0];
    for (int i = 0; i < groups.length; ++i) {
      if (groupValid[i]) {
        maxDiff = Math.max(maxDiff, groups[i][0] - prevValue);
        prevValue = groups[i][1];
      }
    }
    return maxDiff;
  }
}
