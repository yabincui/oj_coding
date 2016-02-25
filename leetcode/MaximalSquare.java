import java.util.*;

public class MaximalSquare {
  public int maximalSquare(char[][] matrix) {
    if (matrix.length == 0 || matrix[0].length == 0) {
      return 0;
    }
    int n = matrix[0].length;
    int[] s = new int[n + 1];
    int maxArea = 0;
    for (int i = 0; i < matrix.length; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == '1') {
          s[j]++;
        } else {
          s[j] = 0;
        }
      }
      Stack<Integer> stack = new Stack<Integer>();
      for (int j = 0; j <= n; ) {
        if (stack.empty() || s[stack.peek()] <= s[j]) {
          stack.push(j);
          ++j;
        } else if (s[stack.peek()] > s[j]) {
          int h = s[stack.pop()];
          int w = (stack.empty() ? j : (j - stack.peek() - 1));
          maxArea = Math.max(maxArea, Math.min(h, w) * Math.min(h, w));
        }
      }
    }
    return maxArea;
  }
}
