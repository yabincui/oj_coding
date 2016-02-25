import java.util.*;

public class WiggleSort {
  public void wiggleSort(int[] nums) {
    Arrays.sort(nums);
    for (int i = 1; i + 1 < nums.length; i += 2) {
      int temp = nums[i];
      nums[i] = nums[i + 1];
      nums[i + 1] = temp;
    }
  }
}
