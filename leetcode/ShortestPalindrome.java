import java.util.*;

public class ShortestPalindrome {
  public String shortestPalindrome(String s) {
    int n = s.length();
    if (n == 0) {
      return s;
    }
    int[][] record = getPalindromeCount(s);
    int copy_index = -1;
    for (int i = n - 1; i >= 0; --i) {
      if (i - record[i][1] + 1 == 0) {
        copy_index = i + record[i][1];
        break;
      }
      if (i - 1 - record[i][0] + 1 == 0) {
        copy_index = i + record[i][0];
        break;
      }
    }
    StringBuilder builder = new StringBuilder();
    for (int i = n - 1; i >= copy_index; --i) {
      builder.append(s.charAt(i));
    }
    builder.append(s);
    return builder.toString();
  }

  int[][] getPalindromeCount(String s) {
    int n = s.length();
    // record[i][0] is the palindrome count using s[i-1] and s[i] as the center.
    // record[i][1] is the palindrome count using s[i] as the center.
    int[][] record = new int[n][2];
    record[0][0] = 0;
    record[0][1] = 1;
    int farReachLeft = 0;
    int farReachRight = 0;
    for (int i = 1; i < n; ++i) {
      // Use s[i-1] and s[i] as the center.
      int j = 0;
      if (farReachRight >= i) {
        int reflect = farReachLeft + (farReachRight - i + 1);
        j = Math.min(record[reflect][0], farReachRight + 1 - i);
      }
      for (; i - 1 - j >= 0 && i + j < n; ++j) {
        if (s.charAt(i - 1 - j) != s.charAt(i + j)) {
          break;
        }
      }
      record[i][0] = j;
      if (j > 0 && farReachRight < i + j - 1) {
        farReachLeft = i - 1 - j + 1;
        farReachRight = i + j - 1;
      }
      // Use s[i] as the center.
      j = 1;
      if (farReachRight >= i) {
        int reflect = farReachLeft + (farReachRight - i);
        j = Math.min(record[reflect][1], farReachRight + 1 - i);
      }
      for (; i - j >= 0 && i + j < n; ++j) {
        if (s.charAt(i - j) != s.charAt(i + j)) {
          break;
        }
      }
      record[i][1] = j;
      if (j > 0 && farReachRight < i + j - 1) {
        farReachLeft = i - j + 1;
        farReachRight = i + j - 1;
      }
    }
    return record;
  }
}
