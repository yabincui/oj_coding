import org.junit.*;
import static org.junit.Assert.*;

public class MakePairsTest {
  MakePairs pair = new MakePairs();

  @Test
  public void test() {
    assertEquals(true, pair.makePair(new int[]{1, 2, 3}, new int[]{4, 5, 6}, 7));
  }
}
