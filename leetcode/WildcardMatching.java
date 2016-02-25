public class WildcardMatching {

  // Normal DP, O(m * n) time, O(m * n) space.
  public boolean isMatch(String s, String p) {
    int m = s.length();
    int n = p.length();
    boolean[][] dp = new boolean[m + 1][n + 1]; 

    dp[0][0] = true;
    for (int j = 1; j <= n; ++j) {
      if (p.charAt(j - 1) == '*') {
        dp[0][j] = dp[0][j - 1];
      } else {
        dp[0][j] = false;
      }
    }
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (p.charAt(j - 1) == '?') {
          dp[i][j] = dp[i - 1][j - 1];
        } else if (p.charAt(j - 1) == '*') {
          dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
          
        } else if (p.charAt(j - 1) == s.charAt(i - 1)) {
          dp[i][j] = dp[i - 1][j - 1];
        }
      }
    }
    return dp[m][n];
  }
  
  // DP, O(m * n) time, O(n) space.
  public boolean isMatch2(String s, String p) {
    int m = s.length();
    int n = p.length();
    boolean[][] dp = new boolean[2][n + 1]; 

    dp[0][0] = true;
    for (int j = 1; j <= n; ++j) {
      if (p.charAt(j - 1) == '*') {
        dp[0][j] = dp[0][j - 1];
      } else {
        dp[0][j] = false;
      }
    }
    int curpos = 1;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (p.charAt(j - 1) == '?') {
          dp[curpos][j] = dp[1 - curpos][j - 1];
        } else if (p.charAt(j - 1) == '*') {
          dp[curpos][j] = dp[1 - curpos][j] || dp[curpos][j - 1];
          
        } else if (p.charAt(j - 1) == s.charAt(i - 1)) {
          dp[curpos][j] = dp[1 - curpos][j - 1];
        }
      }
      curpos = 1 - curpos;
    }
    return dp[1 - curpos][n];
  }
  
  // Preprocess pattern characters not *, becomes O(m + n) time, O(n) space in special cases.
  public boolean isMatch3(String s, String p) {
    int m = s.length();
    int n = p.length();
    int sPos = 0;
    boolean lastIsStar = false;
    for (int pPos = 0; pPos < n;) {
      if (p.charAt(pPos) == '*') {
        lastIsStar = true;
        ++pPos;
        continue;
      }
      int pEnd = pPos;
      while (pEnd < n && p.charAt(pEnd) != '*') {
        ++pEnd;
      }
      if (pEnd == n) {
        int len = pEnd - pPos;
        if (matchString(s, m - len, p, pPos, pEnd - 1)) {
          if ((lastIsStar && m - len >= sPos) || m - len == sPos) {
            return true;
          }
        }
        return false;
      }
      int matchPos = findFirstMatchPos(s, sPos, p.substring(pPos, pEnd));
      if (matchPos == -1 || (!lastIsStar && sPos != matchPos)) {
        return false;
      }
      sPos = pEnd - pPos + matchPos;
      pPos = pEnd;
      lastIsStar = false;
    }
    if (sPos == m || lastIsStar) {
      return true;
    }
    return false;
  }

  // Can be optimized to O(m + n).
  int findFirstMatchPos(String s, int startPos, String p) {
    for (int i = startPos; i <= s.length() - p.length(); ++i) {
      if (matchString(s, i, p, 0, p.length() - 1)) {
        return i;
      }
    }
    return -1;
  }

  boolean matchString(String s, int start1, String p, int start2, int end2) {
    if (start1 < 0) {
      return false;
    }
    int len = end2 - start2 + 1;
    for (int i = 0; i < len; ++i) {
      if (!(s.charAt(i + start1) == p.charAt(i + start2) || p.charAt(i + start2) == '?')) {
        return false;
      }
    }
    return true;
  }
}
