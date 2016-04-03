public class RangeSumQueryMutable {
  class NumArray {
    private long[] BIT;

    public NumArray(int[] nums) {
      BIT = new long[nums.length + 1];
      for (int i = 0; i < nums.length; ++i) {
        addBitValue(i + 1, nums[i]);
      }
    }

    void update(int i, int val) {
      int pos = i + 1;
      int oldValue = (int)(queryBitSum(pos) - queryBitSum(pos - 1));
      int diff = val - oldValue;
      addBitValue(pos, diff);
    }

    public int sumRange(int i, int j) {
      return (int)(queryBitSum(j + 1) - queryBitSum(i));
    }

    private void addBitValue(int i, int value) {
      while (i < BIT.length) {
        BIT[i] += value;
        i += i & -i;
      }
    }

    private long queryBitSum(int i) {
      long sum = 0;
      while (i != 0) {
        sum += BIT[i];
        i -= i & -i;
      }
      return sum;
    }

  }
}
