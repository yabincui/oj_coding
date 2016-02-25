import org.junit.*;
import static org.junit.Assert.*;

public class ReadSumOfDigitsTest {
  ReadSumOfDigits sum = new ReadSumOfDigits();

  @Test
  public void test() {
    assertEquals("four five", sum.readSum("987654321"));
    assertEquals("zero", sum.readSum("0"));
  }
}
