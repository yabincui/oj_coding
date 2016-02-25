import org.junit.*;
import static org.junit.Assert.*;

public class ConnectedGraphTest {
  ConnectedGraph graph = new ConnectedGraph();

  @Test
  public void test() {
    //assertEquals(0, graph.connectThem(1));
    assertEquals(1, graph.connectThem(2));
    assertEquals(2, graph.connectThem(3));
    assertEquals(3, graph.connectThem(4));
    assertEquals(4, graph.connectThem(5));
    assertEquals(6, graph.connectThem(6));
    assertEquals(14, graph.connectThem(11));
    assertEquals(55, graph.connectThem(30));
    assertEquals(48, graph.connectThem(27));
    assertEquals(46, graph.connectThem(26));
    assertEquals(18, graph.connectThem(13));
    assertEquals(53, graph.connectThem(29));
    assertEquals(22, graph.connectThem(15));
    assertEquals(16, graph.connectThem(12));
    assertEquals(7, graph.connectThem(7));
    assertEquals(34, graph.connectThem(21));
    assertEquals(24, graph.connectThem(16));
    assertEquals(44, graph.connectThem(25));
    assertEquals(26, graph.connectThem(17));
    assertEquals(41, graph.connectThem(24));
    assertEquals(32, graph.connectThem(20));
    assertEquals(10, graph.connectThem(9));

    /*
    for (int i = 4; i <= 30; ++i) {
      System.out.printf("connectThem(%d) = %d\n", i, graph.connectThem(i));
    }
    */
  }
}
