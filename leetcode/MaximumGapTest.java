import org.junit.*;
import static org.junit.Assert.*;

public class MaximumGapTest {
  MaximumGap gap = new MaximumGap();

  @Test
  public void test() {
    assertEquals(97, gap.maximumGap(new int[]{100, 3, 2, 1}));
    assertEquals(9999999, gap.maximumGap(new int[]{1, 10000000}));
  }
}
