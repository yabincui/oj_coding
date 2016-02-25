import java.util.*;
import org.junit.*;
import static org.junit.Assert.*;

public class MakeSequenceInAscendingOrderTest {
  MakeSequenceInAscendingOrder order = new MakeSequenceInAscendingOrder();

  @Test
  public void test() {
    assertEquals(2, order.makeSequence(new int[]{1, 1, 3, 1}));
    int n = 1000000;
    int[] s = new int[n];
    for (int i = 0; i < s.length; ++i) {
      s[i] = 1000000;
    }
    assertEquals(999999, order.makeSequence(s));
    assertEquals(6, order.makeSequence(new int[]{7, 8, 9, 10, 1, 2, 3, 4, 5, 6}));
    assertEquals(6, order.makeSequence0(new int[]{7, 8, 9, 10, 1, 2, 3, 4, 5, 6}));
  }
}
