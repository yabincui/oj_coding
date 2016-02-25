import org.junit.*;
import static org.junit.Assert.*;

public class WildcardMatchingTest {
  WildcardMatching match = new WildcardMatching();

  @Test
  public void test1() {
    assertEquals(false, match.isMatch3("b", "?*?"));
    assertEquals(false, match.isMatch3("aaab", "b**"));
  }
}
