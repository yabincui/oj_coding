public class MakeSequenceInAscendingOrder {
  public int makeSequence0(int[] a) {
    int n = a.length;
    // dp[i][j] means for a[0..i-1], the minimum value achieved when j replacements are applied.
    int[][] dp = new int[n + 1][n + 1];
    int[] minReplacements = new int[n + 1];
    dp[0][0] = 0;
    minReplacements[0] = 0;
    for (int i = 1; i <= n; ++i) {
      int curValue = a[i - 1];
      int prevMinReplace = minReplacements[i - 1];
      int curMinReplace = -1;
      for (int j = prevMinReplace; j <= i; ++j) {
        int minValue = Integer.MAX_VALUE;
        if (j <= i - 1 && dp[i - 1][j] < curValue) {
          // Not change a[i - 1].
          minValue = Math.min(minValue, curValue);
        }
        if (j > prevMinReplace) {
          // Change a[i - 1] to smaller or bigger.
          minValue = Math.min(minValue, dp[i - 1][j - 1] + 1);
        }
        if (minValue != Integer.MAX_VALUE) {
          if (curMinReplace == -1) {
            curMinReplace = j;
          }
          dp[i][j] = minValue;
        }
      }
      minReplacements[i] = curMinReplace;
    }
    return minReplacements[n];
  }

  int searchSelected(int[] s, int left, int right, int value) {
    while (left <= right) {
      int mid = (left + right) / 2;
      if (s[mid] < value && (mid - 1 < left || s[mid - 1] >= value)) {
        return mid;
      }
      if (s[mid] < value) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return -1;
  }

  public int makeSequence1(int[] a) {
    int n = a.length;
    int[] dp = new int[n + 1];
    dp[0] = 0;
    int minReplacement = 0;
    for (int i = 1; i <= n; ++i) {
      int selected = searchSelected(dp, minReplacement, i - 1, a[i - 1]);
      for (int j = i; j > minReplacement; --j) {
        dp[j] = dp[j - 1] + 1;
      }
      dp[selected] = a[i - 1];
      if (selected != minReplacement) {
        ++minReplacement;
      }
    }
    return minReplacement;
  }

  public int makeSequence(int[] a) {
    int n = a.length;
    int[] dp = new int[n + 1];
    dp[n] = 0;
    int base = 0;
    int possibleLength = 1;
    for (int i = 1; i <= n; ++i) {
      int selected = searchSelected(dp, n - possibleLength + 1, n, a[i - 1] - base);
      base++;
      if (selected != -1) {
        dp[selected - 1] = a[i - 1] - base;
      }
      if (selected == n - possibleLength + 1) {
        possibleLength++;
      }
    }
    int result = n - possibleLength + 1;
    return result;
  }
}
