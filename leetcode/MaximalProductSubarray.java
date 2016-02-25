public class MaximalProductSubarray {
  public int maxProduct(int[] nums) {
    long maxArea = nums[0];
    long curMinArea = nums[0];
    long curMaxArea = nums[0];
    for (int i = 1; i < nums.length; ++i) {
      long nextMinArea = 0;
      long nextMaxArea = 0;
      if (nums[i] > 0) {
        nextMaxArea = Math.max(1, curMaxArea) * nums[i];
        nextMinArea = Math.min(1, curMinArea) * nums[i];
      } else if (nums[i] < 0) {
        nextMaxArea = Math.min(1, curMinArea) * nums[i];
        nextMinArea = Math.max(1, curMaxArea) * nums[i];
      }
      curMinArea = nextMinArea;
      curMaxArea = nextMaxArea;
      if (curMaxArea > maxArea) {
        maxArea = curMaxArea;
      }
    }
    return (int)maxArea;
  }
}
