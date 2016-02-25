import static org.junit.Assert.assertEquals;
import org.junit.Test;

class Combination {

  // Calculate C(n, k) with DP.
  int calculateCombination(int n, int k) {
    int[][] dp = new int [n + 1][k + 1];
    for (int i = 1; i <= n; ++i) {
      dp[i][0] = 1;
    }
    for (int i = 1; i <= n; ++i) {
      dp[i][0] = 1;
			if (i <= k) {
      	dp[i][i] = 1;
			}
      for (int j = 1; j < i && j <= k; ++j) {
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      }
    }
    return dp[n][k];
  }
}

public class CombinationTest {
  
  @Test
  public void calculateCombination1() {
    Combination combination = new Combination();
    assertEquals(1, combination.calculateCombination(2, 0));
    assertEquals(2, combination.calculateCombination(2, 1));
    assertEquals(1, combination.calculateCombination(2, 2));

    assertEquals(0, combination.calculateCombination(0, 1));
    assertEquals(1, combination.calculateCombination(100, 100));
    assertEquals(3, combination.calculateCombination(3, 2));
    assertEquals(0, combination.calculateCombination(3, 5));
  }
}
