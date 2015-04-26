import static org.junit.Assert.assertEquals;
import org.junit.Test;

class BestEditDistance {
  int addNoOverflow(int a, int b) {
    if (a < Integer.MAX_VALUE - b) {
      return a + b;
    }
    return Integer.MAX_VALUE;
  }
  
  // Find the best edit distance between s and substring of t.
  int findBestEditDistance(String s, String t, int deletionCost, int insertionCost,
                           int substitutionCost) {
    int bestEd = Integer.MAX_VALUE;
    for (int i = 0; i <= t.length(); ++i) {
      bestEd = Math.min(bestEd, findBestEditDistanceOfTPrefix(s, t.substring(i), deletionCost,
                        insertionCost, substitutionCost));
    }
    return bestEd;
  }

  int findBestEditDistanceOfTPrefix(String s, String t, int deletionCost, int insertionCost,
                           int substitutionCost) {
    int[][] dp = new int[s.length() + 1][t.length() + 1];
    dp[0][0] = 0;
    for (int i = 1; i <= s.length(); ++i) {
      dp[i][0] = addNoOverflow(deletionCost, dp[i - 1][0]);
    }
    for (int j = 1; j <= t.length(); ++j) {
      dp[0][j] = addNoOverflow(insertionCost, dp[0][j - 1]);
    }
    for (int i = 1; i <= s.length(); ++i) {
      for (int j = 1; j <= t.length(); ++j) {
        int minCost = Integer.MAX_VALUE;
        // Substitution.
        if (s.charAt(i - 1) == t.charAt(j - 1)) {
          minCost = Math.min(minCost, dp[i - 1][j - 1]);
        } else {
          minCost = Math.min(minCost, addNoOverflow(dp[i - 1][j - 1], substitutionCost));
        }
        // Insertion.
        minCost = Math.min(minCost, addNoOverflow(dp[i][j - 1], insertionCost));
        // Deletion.
        minCost = Math.min(minCost, addNoOverflow(dp[i - 1][j], deletionCost));
        dp[i][j] = minCost;
      }
    }
    int bestEd = Integer.MAX_VALUE;
    for (int j = 0; j <= t.length(); ++j) {
      bestEd = Math.min(bestEd, dp[s.length()][j]);
    }
    return bestEd;
  }

  int findBestEditDistance2(String s, String t, int deletionCost, int insertionCost,
                            int substitutionCost) {
     if (s == null) {
      s = "";
    }
    if (t == null) {
      t = "";
    }

    int[][] dp = new int[s.length() + 1][t.length() + 1];
    dp[0][0] = 0;
    // Set dp[0][j] to 0, to make the distance unrelated to the start pos in t.
    for (int j = 1; j <= t.length(); ++j) {
      dp[0][j] = 0;
    }
    for (int i = 1; i <= s.length(); ++i) {
      dp[i][0] = addNoOverflow(dp[i - 1][0], deletionCost);
      for (int j = 1; j <= t.length(); ++j) {
        int minCost = Integer.MAX_VALUE;
        if (s.charAt(i - 1) == t.charAt(j - 1)) {
          minCost = Math.min(minCost, dp[i - 1][j - 1]);
        } else {
          minCost = Math.min(minCost, addNoOverflow(dp[i - 1][j - 1], substitutionCost));
        }
        minCost = Math.min(minCost, addNoOverflow(dp[i - 1][j], deletionCost));
        minCost = Math.min(minCost, addNoOverflow(dp[i][j - 1], insertionCost));
        dp[i][j] = minCost;
      }
    }
    int bestEd = Integer.MAX_VALUE;
    for (int j = 0; j <= t.length(); ++j) {
      bestEd = Math.min(bestEd, dp[s.length()][j]);
    }
    return bestEd;
  }
}

public class BestEditDistanceTest {
  @Test
  public void bestEditDistanceTest() {
    BestEditDistance bestEd = new BestEditDistance();
    assertEquals(0, bestEd.findBestEditDistance("", "", 1, 1, 1));
    assertEquals(3, bestEd.findBestEditDistance("abc", "", 1, 1, 1));
    assertEquals(0, bestEd.findBestEditDistance("abc", "eabcd", 1, 1, 1));
    assertEquals(3, bestEd.findBestEditDistance("abc", "edf", 1, 1, 1));
  }
  @Test
  public void bestEditDistanceTest2() {
    BestEditDistance bestEd = new BestEditDistance();
    assertEquals(0, bestEd.findBestEditDistance2("", "", 1, 1, 1));
    assertEquals(3, bestEd.findBestEditDistance2("abc", "", 1, 1, 1));
    assertEquals(0, bestEd.findBestEditDistance2("abc", "eabcd", 1, 1, 1));
    assertEquals(3, bestEd.findBestEditDistance2("abc", "edf", 1, 1, 1));
  }
}
