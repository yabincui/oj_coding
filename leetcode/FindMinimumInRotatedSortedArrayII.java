public class FindMinimumInRotatedSortedArrayII {
  public int findMin(int[] nums) {
    if (nums[0] < nums[nums.length - 1]) {
      return nums[0];
    }
    int lastPos = nums.length - 1;
    while (lastPos > 0 && nums[0] == nums[lastPos]) {
      --lastPos;
    }
    if (nums[lastPos] >= nums[0]) {
      return nums[0];
    }
    int low = 0;
    int high = lastPos;
    while (low + 1 < high) {
      int mid = (low + high) / 2;
      if (nums[mid] >= nums[0]) {
        low = mid + 1;
      } else {
        high = mid;
      }
    }
    int min = nums[low];
    if (low + 1 <= high && min > nums[low + 1]) {
      min = nums[low + 1];
    }
    return min;
  }
}
