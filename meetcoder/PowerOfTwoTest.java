import org.junit.*;
import static org.junit.Assert.*;

public class PowerOfTwoTest {
  PowerOfTwo pow = new PowerOfTwo();

  @Test
  public void test() {
    assertEquals(false, pow.isPowerOf2(0));
    assertEquals(true, pow.isPowerOf2(1));
  }
}
