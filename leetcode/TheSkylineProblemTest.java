import java.util.*;
import org.junit.*;
import static org.junit.Assert.*;

public class TheSkylineProblemTest {
  TheSkylineProblem sky = new TheSkylineProblem();

  @Test
  public void test() {
    int[][] buildings = new int[][] {
      {2, 9, 10},
      {3, 7, 15},
      {5, 12, 12},
      {15, 20, 10},
      {19, 24, 8},
    };
    List<int[]> res = sky.getSkyline(buildings);
    int[][] exp = new int[][] {
      {2, 10},
      {3, 15},
      {7, 12},
      {12, 0},
      {15, 10},
      {20, 8},
      {24, 0},
    };
    assertEquals(exp.length, res.size());
    for (int i = 0; i < exp.length; ++i) {
      assertArrayEquals(exp[i], res.get(i));
    }
  }
}
