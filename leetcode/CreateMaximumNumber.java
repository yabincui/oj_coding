import java.util.*;

public class CreateMaximumNumber {
  public int[] maxNumber(int[] nums1, int[] nums2, int k) {
    String[] bestK1 = getBestKLength(nums1, Integer.min(k, nums1.length));
    for (int i = 0; i < bestK1.length; ++i) {
      //System.out.printf("bestK1[%d] = %s\n", i, bestK1[i]);
    }
    String[] bestK2 = getBestKLength(nums2, Integer.min(k, nums2.length));
    for (int i = 0; i < bestK2.length; ++i) {
      //System.out.printf("bestK2[%d] = %s\n", i, bestK2[i]);
    }
    String best = null;
    for (int t1 = 0; t1 <= k; ++t1) {
      int t2 = k - t1;
      if (t1 > bestK1.length || t2 > bestK2.length) {
        continue;
      }
      String curBest = "";
      if (t1 == 0) {
        curBest = bestK2[t2 - 1];
      } else if (t2 == 0) {
        curBest = bestK1[t1 - 1];
      } else {
        curBest = combineString(bestK1[t1 - 1], bestK2[t2 - 1]);
      } 
      if (best == null || curBest.compareTo(best) > 0) {
        best = curBest;
      }
    }
    int[] result = new int[k];
    for (int i = 0; i < k; ++i) {
      result[i] = best.charAt(i) - '0';
    }
    return result;
  }

  String combineString(String s1, String s2) {
    char[] buf = new char[s1.length() + s2.length()];
    int p = 0;
    int q = 0;
    int i = 0;
    while (p != s1.length() && q != s2.length()) {
      if (s1.substring(p).compareTo(s2.substring(q)) > 0) {
        buf[i++] = s1.charAt(p++);
      } else {
        buf[i++] = s2.charAt(q++);
      }
    }
    while (p != s1.length()) {
      buf[i++] = s1.charAt(p++);
    }
    while (q != s2.length()) {
      buf[i++] = s2.charAt(q++);
    }
    return new String(buf);
  }

  String[] getBestKLength(int[] s, int k) {
    String[] result = new String[k];
    int n = s.length;
    if (n == 0) {
      return result;
    }
    // dp[i] is the max substring for s[0..i]
    String[] dp = new String[n];
    // for length 1.
    dp[0] = "" + s[0];
    for (int i = 1; i < n; ++i) {
      String cur = "" + s[i];
      if (cur.compareTo(dp[i - 1]) > 0) {
        dp[i] = cur;
      } else {
        dp[i] = dp[i - 1];
      }
    }
    result[0] = dp[n - 1];
    // for length 2 - k.
    for (int len = 2; len <= k; ++len) {
      String prefix = dp[len - 1];
      dp[len - 1] = dp[len - 2] + s[len - 1];
      for (int i = len; i < n; ++i) {
        String next = dp[i];
        String t = prefix + s[i];
        if (t.compareTo(dp[i - 1]) > 0) {
          dp[i] = t;
        } else {
          dp[i] = dp[i - 1];
        }
        prefix = next;
      }
      result[len - 1] = dp[n - 1];
    }
    return result;
  }

  public static void main(String[] args) {
    CreateMaximumNumber obj = new CreateMaximumNumber();
    int[] n1 = new int[]{3, 4, 6, 5};
    int[] n2 = new int[]{9, 1, 2, 5, 8, 3};
    int[] res = obj.maxNumber(n1, n2, 5);
    for (int i = 0; i < res.length; ++i) {
      System.out.printf("%d ", res[i]);
    }
    System.out.printf("\n");
  }
}
