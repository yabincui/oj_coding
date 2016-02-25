public class MaxSubArraySum {
  public int getMaxSubarraySum(int[] A) {
    int n = A.length;
    int[] maxPrev = new int[n];
    maxPrev[0] = A[0];
    for (int i = 1; i < n; ++i) {
      maxPrev[i] = Math.max(maxPrev[i - 1], A[i]);
    }
    int[] maxPost = new int[n];
    maxPost[n - 1] = A[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      maxPost[i] = Math.max(maxPost[i + 1], A[i]);
    }
    int begin = 0, end = 0;
    int minValue = A[0];
    int sum = A[0];
    int result = A[0];

    for (end = 1; end < n; ++end) {
      if (sum < 0) {
        sum = A[end];
        minValue = A[end];
        begin = end;
        result = Math.max(result, sum);
        continue;
      }
      sum += A[end];
      minValue = Math.min(minValue, A[end]);
      int swapValue = minValue;
      if (begin > 0) {
        swapValue = Math.max(swapValue, maxPrev[begin - 1]);
      }
      if (end < n - 1) {
        swapValue = Math.max(swapValue, maxPost[end + 1]);
      }
      int temp = sum + swapValue - minValue;
      result = Math.max(result, temp);
    }
    return result;
  }
}
