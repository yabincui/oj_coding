import org.junit.*;
import static org.junit.Assert.*;

public class CoverTheMagicBoardTest {
  CoverTheMagicBoard board = new CoverTheMagicBoard();

  @Test
  public void test() {
    assertEquals(0, board.coverBoard(1, 0));
    assertEquals(1, board.coverBoard(1, 1));
    assertEquals(1, board.coverBoard(2, 1));
    assertEquals(2, board.coverBoard(2, 2));
    assertEquals(11, board.coverBoard(4, 3));
    assertEquals(6402693, board.coverBoard(1000000, 7));
    assertEquals(9694700, board.coverBoard(987654321, 3));
  }
}
