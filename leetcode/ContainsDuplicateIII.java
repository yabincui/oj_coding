import java.util.*;

public class ContainsDuplicateIII {
  public boolean containsNearbyAlmostDuplicate(int[] nums, int k, int t) {
    TreeSet<Integer> set = new TreeSet<Integer>();
    for (int i = 0; i < nums.length; ++i) {
      if (i > k) {
        set.remove(nums[i-k-1]);
      }
      Integer value = set.ceiling(nums[i]);
      if (value != null && (long)value - nums[i] <= t) {
        return true;
      }
      value = set.floor(nums[i]);
      if (value != null && (long)nums[i] - value <= t) {
        return true;
      }
      set.add(nums[i]);
    }
    return false;
  }
}
