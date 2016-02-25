import org.junit.*;
import static org.junit.Assert.*;

public class PalindromicSubstringsTest {
  PalindromicSubstrings palin = new PalindromicSubstrings();

  @Test
  public void test() {
    assertEquals(4, palin.countPalindromicSubstrings("aba"));
  }
}
