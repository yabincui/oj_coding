import static org.junit.Assert.assertEquals;
import org.junit.Test;
import java.util.ArrayList;

class EditDistanceOperation {
  int addNoOverflow(int a, int b) {
    if (a < Integer.MAX_VALUE - b) {
      return a + b;
    }
    return Integer.MAX_VALUE;
  }

  static class Operation {
    char op;
    int pos;
    char value;

    Operation(char op, int pos) {
      this.op = op;
      this.pos = pos;
    }
    Operation(char op, int pos, char value) {
      this.op = op;
      this.pos = pos;
      this.value = value;
    }
  };

  // Return operations of changing s into t.
  public int editDistance(String s, String t, int insertionCost, int deletionCost, int substitutionCost,
                          ArrayList<Operation> operations) {
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

    operations.clear();
    int curS = s.length();
    int curT = t.length();
    while (curS != 0 || curT != 0) {
      // Try substitution.
      if (curS != 0 && curT != 0) {
        if (s.charAt(curS - 1) == t.charAt(curT - 1)) {
          if (dp[curS][curT] == dp[curS - 1][curT - 1]) {
            --curS;
            --curT;
            continue;
          }
        } else {
          if (dp[curS][curT] == addNoOverflow(dp[curS - 1][curT - 1], substitutionCost)) {
            operations.add(new Operation('S', curS - 1, t.charAt(curT - 1)));
            --curS;
            --curT;
            continue;
          }
        }
      }

      // Try insertion.
      if (curT != 0) {
        if (dp[curS][curT] == addNoOverflow(dp[curS][curT - 1], insertionCost)) {
          operations.add(new Operation('I', curS, t.charAt(curT - 1)));
          --curT;
          continue;
        }
      }

      // Try deletion.
      if (curS != 0) {
        if (dp[curS][curT] == addNoOverflow(dp[curS - 1][curT], deletionCost)) {
          operations.add(new Operation('D', curS - 1));
          --curS;
          continue;
        }
      }
    }
    return dp[s.length()][t.length()];
  }

  String changeStringByOperations(String s, ArrayList<Operation> operations) {
    StringBuilder builder = new StringBuilder(s);
    for (Operation operation : operations) {
      if (operation.op == 'D') {
        builder.deleteCharAt(operation.pos);
      } else if (operation.op == 'I') {
        builder.insert(operation.pos, operation.value);
      } else if (operation.op == 'S') {
        builder.setCharAt(operation.pos, operation.value);
      }
    }
    return builder.toString();
  }
}

public class EditDistanceOperationTest {
  @Test
  public void editDistanceTest1() {
    EditDistanceOperation ed = new EditDistanceOperation();
    ArrayList<EditDistanceOperation.Operation> operations =
      new ArrayList<EditDistanceOperation.Operation>();

    assertEquals(0, ed.editDistance("abc", "edf", 0, 0, 0, operations));
    assertEquals("edf", ed.changeStringByOperations("abc", operations));

    assertEquals(0, ed.editDistance("", "", 1, 1, 1, operations));
    assertEquals(0, operations.size());
    assertEquals("", ed.changeStringByOperations("", operations));

    assertEquals(0, ed.editDistance("abc", "abc", 1, 1, 1, operations));
    assertEquals(0, operations.size());
    assertEquals("abc", ed.changeStringByOperations("abc", operations));

    assertEquals(0, ed.editDistance("abcd", "abc", 1, 0, 1, operations));
    assertEquals(1, operations.size());
    assertEquals("abc", ed.changeStringByOperations("abcd", operations));

    assertEquals(1, ed.editDistance("abc", "adc", 2, 2, 1, operations));
    assertEquals(1, operations.size());
    assertEquals("adc", ed.changeStringByOperations("abc", operations));

    assertEquals(1, ed.editDistance("abc", "dabc", 1, 0, 0, operations));
    assertEquals(1, operations.size());
    assertEquals("dabc", ed.changeStringByOperations("abc", operations));

    assertEquals(5, ed.editDistance("kitten", "sitting", 1, 1, 10, operations));
    assertEquals(5, operations.size());
    assertEquals("sitting", ed.changeStringByOperations("kitten", operations));

    assertEquals(Integer.MAX_VALUE, ed.editDistance("ab", "ed", Integer.MAX_VALUE,
                 Integer.MAX_VALUE, Integer.MAX_VALUE, operations));
    assertEquals("ed", ed.changeStringByOperations("ab", operations));

    assertEquals(Integer.MAX_VALUE, ed.editDistance("ab", "", Integer.MAX_VALUE,
                 Integer.MAX_VALUE, Integer.MAX_VALUE, operations));
    assertEquals("", ed.changeStringByOperations("ab", operations));

    assertEquals(Integer.MAX_VALUE, ed.editDistance("", "ab", Integer.MAX_VALUE,
                 Integer.MAX_VALUE, Integer.MAX_VALUE, operations));
    assertEquals("ab", ed.changeStringByOperations("", operations));

    assertEquals(0, ed.editDistance("", null, 1, 2, 3, operations));
    assertEquals(0, operations.size());
    assertEquals("", ed.changeStringByOperations("", operations));

    assertEquals(1, ed.editDistance("", "a", 1, 2, 3, operations));
    assertEquals(1, operations.size());
    assertEquals("a", ed.changeStringByOperations("", operations));

    assertEquals(2, ed.editDistance("a", "", 1, 2, 3, operations));
    assertEquals(1, operations.size());
    assertEquals("", ed.changeStringByOperations("a", operations));

    assertEquals(3, ed.editDistance("b", "a", 1, 2, 4, operations));
    assertEquals(2, operations.size());
    assertEquals("a", ed.changeStringByOperations("b", operations));

    assertEquals(1, ed.editDistance("ac", "ad", 1, 1, 1, operations));
    assertEquals(1, operations.size());
    assertEquals("ad", ed.changeStringByOperations("ac", operations));

    assertEquals(2, ed.editDistance("ab", null, 1, 1, 1, operations));
    assertEquals(2, operations.size());
    assertEquals("", ed.changeStringByOperations("ab", operations));

    assertEquals(2, ed.editDistance(null, "ab", 1, 1, 1, operations));
    assertEquals(2, operations.size());
    assertEquals("ab", ed.changeStringByOperations("", operations));

    assertEquals(Integer.MAX_VALUE, ed.editDistance("ab", "a", Integer.MAX_VALUE,
                 Integer.MAX_VALUE, Integer.MAX_VALUE, operations));
    assertEquals("a", ed.changeStringByOperations("ab", operations));

    assertEquals(Integer.MAX_VALUE, ed.editDistance("ab", "abc", Integer.MAX_VALUE,
                 Integer.MAX_VALUE, Integer.MAX_VALUE, operations));
    assertEquals("abc", ed.changeStringByOperations("ab", operations));
  }

  @Test
  public void addNoOverflowTest() {
    EditDistanceOperation ed = new EditDistanceOperation();
    assertEquals(2, ed.addNoOverflow(1, 1));
    assertEquals(Integer.MAX_VALUE, ed.addNoOverflow(Integer.MAX_VALUE - 1, Integer.MAX_VALUE));
    assertEquals(Integer.MAX_VALUE, ed.addNoOverflow(Integer.MAX_VALUE, Integer.MAX_VALUE));
  }

  @Test
  public void changeStringByOperationTest() {
    EditDistanceOperation ed = new EditDistanceOperation();
    ArrayList<EditDistanceOperation.Operation> operations =
      new ArrayList<EditDistanceOperation.Operation>();

    assertEquals("abc", ed.changeStringByOperations("abc", operations));
    
    operations.add(new EditDistanceOperation.Operation('D', 1));
    assertEquals("ac", ed.changeStringByOperations("abc", operations));
    operations.clear();

    operations.add(new EditDistanceOperation.Operation('I', 1, 'b'));
    assertEquals("abc", ed.changeStringByOperations("ac", operations));
    operations.clear();

    operations.add(new EditDistanceOperation.Operation('S', 1, 'd'));
    assertEquals("adc", ed.changeStringByOperations("abc", operations));
    operations.clear();
  }
}

