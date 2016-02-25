import static org.junit.Assert.assertEquals;
import org.junit.Test;

class EditDistance {
  int addNoOverflow(int a, int b) {
    if (a < Integer.MAX_VALUE - b) {
      return a + b;
    }
    return Integer.MAX_VALUE;
  }

  // Calculate the minimum cost of changing s into t, by insertion/deletion/substitution.
  public int editDistance(String s, String t, int insertionCost, int deletionCost, int substitutionCost) {
    if (s == null) {
      s = "";
    }
    if (t == null) {
      t = "";
    }

    int[][] dp = new int[s.length() + 1][t.length() + 1];
    dp[0][0] = 0;
    for (int j = 1; j <= t.length(); ++j) {
      dp[0][j] = addNoOverflow(dp[0][j - 1], insertionCost);
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
    return dp[s.length()][t.length()];
  }
}

public class EditDistanceTest {
  @Test
  public void editDistanceTest1() {
    EditDistance ed = new EditDistance();
    assertEquals(0, ed.editDistance("abc", "edf", 0, 0, 0));
    assertEquals(0, ed.editDistance("", "", 1, 1, 1));
    assertEquals(0, ed.editDistance("abc", "abc", 1, 1, 1));
    assertEquals(0, ed.editDistance("abcd", "abc", 1, 0, 1));
    assertEquals(1, ed.editDistance("abc", "adc", 2, 2, 1));
    assertEquals(1, ed.editDistance("abc", "dabc", 1, 0, 0));
    assertEquals(5, ed.editDistance("kitten", "sitting", 1, 1, 10));
    assertEquals(Integer.MAX_VALUE, ed.editDistance("ab", "ed", Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE));
    assertEquals(Integer.MAX_VALUE, ed.editDistance("ab", "", Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE));
    assertEquals(Integer.MAX_VALUE, ed.editDistance("", "ab", Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE));

    assertEquals(0, ed.editDistance("", null, 1, 2, 3));
    assertEquals(1, ed.editDistance("", "a", 1, 2, 3));
    assertEquals(2, ed.editDistance("a", "", 1, 2, 3));
    assertEquals(3, ed.editDistance("b", "a", 1, 2, 3));
    assertEquals(1, ed.editDistance("ac", "ad", 1, 1, 1));
    assertEquals(2, ed.editDistance("ab", null, 1, 1, 1));
    assertEquals(2, ed.editDistance(null, "ab", 1, 1, 1));
  }

  @Test
  public void addNoOverflowTest() {
    EditDistance ed = new EditDistance();
    assertEquals(2, ed.addNoOverflow(1, 1));
    assertEquals(Integer.MAX_VALUE, ed.addNoOverflow(Integer.MAX_VALUE - 1, Integer.MAX_VALUE));
    assertEquals(Integer.MAX_VALUE, ed.addNoOverflow(Integer.MAX_VALUE, Integer.MAX_VALUE));
  }
}

