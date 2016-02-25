import org.junit.*;
import static org.junit.Assert.*;

public class StringCompressionTest {
  StringCompression comp = new StringCompression();

  @Test
  public void test() {
    assertEquals("a2b1c5a3", comp.compressString("aabcccccaaa"));
  }
}
