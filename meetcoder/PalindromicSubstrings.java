public class PalindromicSubstrings {
  public long countPalindromicSubstrings(String s) {
    int farReachLeft = 0;
    int farReachRight = 0;
    int n = s.length();
    // record[i][0] means the max palindrome nums using s[i-1],s[i] as the center.
    // record[i][1] means the max palindrome nums using s[i] as the center.
    long[][] record = new long[n][2];
    record[0][0] = 1;
    for (int i = 1; i < n; ++i) {
      // Use s[i-1] and s[i] as the center.
      int j = 0;
      if (farReachRight >= i) {
        int reflect = farReachLeft + (farReachRight - (i - 1));
        j = (int)Math.min(record[reflect][0], farReachRight + 1 - i);
      }
      for (; i - 1 - j >= 0 && i + j < n; ++j) {
        if (s.charAt(i - 1 - j) != s.charAt(i + j)) {
          break;
        }
      }
      record[i][0] = j;
      if (j > 0 && farReachRight < i + j - 1) {
        farReachRight = i + j - 1;
        farReachLeft = i - 1 - j + 1;
      }
      // Use s[i] as the center.
      j = 1;
      if (farReachRight >= i) {
        int reflect = farReachLeft + (farReachRight - i);
        j = (int)Math.min(record[reflect][1], farReachRight + 1 - i);
      }
      for (; i - j >= 0 && i + j < n; ++j) {
        if (s.charAt(i - j) != s.charAt(i + j)) {
          break;
        }
      }
      record[i][1] = j;
      if (j > 0 && farReachRight < i + j - 1) {
        farReachRight = i + j - 1;
        farReachLeft = i - j + 1;
      }
    }

    long result = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 2; ++j) {
        result += record[i][j];
      }
    }
    return result;
  }
}
