import org.junit.*;
import static org.junit.Assert.*;

public class MaximizeNumberWithSwapTest {
  MaximizeNumberWithSwap swap = new MaximizeNumberWithSwap();

  @Test
  public void test() {
    assertEquals(201, swap.maximizeResult(102));
    assertEquals(0, swap.maximizeResult(0));
  }
}
