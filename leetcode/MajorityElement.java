public class MajorityElement {
  public int majorityElement(int[] nums) {
    int value = nums[0];
    int count = 1;
    for (int i = 1; i < nums.length; ++i) {
      if (count == 0) {
        value = nums[i];
        count = 1;
      } else if (nums[i] == value) {
        count++;
      } else {
        count--;
      }
    }
    return value;
  }
}
