import org.junit.*;
import static org.junit.Assert.*;

public class ShortestPalindromeTest {
  ShortestPalindrome palin = new ShortestPalindrome();

  @Test
  public void test() {
    assertEquals("aaacecaaa", palin.shortestPalindrome("aacecaaa"));
    assertEquals("dcbabcd", palin.shortestPalindrome("abcd"));
  }
}
