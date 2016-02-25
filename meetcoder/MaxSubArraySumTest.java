import org.junit.*;
import static org.junit.Assert.*;

public class MaxSubArraySumTest {
  MaxSubArraySum sum = new MaxSubArraySum();

  @Test
  public void test() {
    assertEquals(2, sum.getMaxSubarraySum(new int[]{1, -1, 1}));
    assertEquals(45, sum.getMaxSubarraySum(new int[]{1, 2, 3, 4, 5, -1, 9, 7, 8, 6}));
  }
}
