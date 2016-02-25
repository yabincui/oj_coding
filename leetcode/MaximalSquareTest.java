import org.junit.*;
import static org.junit.Assert.*;

public class MaximalSquareTest {
  MaximalSquare square = new MaximalSquare();

  @Test
  public void test() {
    assertEquals(1, square.maximalSquare(new char[][] {
      {'1', '1'}
    }));
    assertEquals(1, square.maximalSquare(new char[][] {
    "00010111".toCharArray(),
    "01100101".toCharArray(),
    "10111101".toCharArray(),
    "00010000".toCharArray(),
    "00100010".toCharArray(),
    "11100111".toCharArray(),
    "10011001".toCharArray(),
    "01001100".toCharArray(),
    "10010000".toCharArray()
    }));
  }
}
