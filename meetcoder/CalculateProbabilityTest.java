import org.junit.*;
import static org.junit.Assert.*;

public class CalculateProbabilityTest {
  CalculateProbability cal = new CalculateProbability();

  @Test
  public void test() {
    assertArrayEquals(new int[]{1, 2}, cal.calculate(1, 1, 1));
  }
}
