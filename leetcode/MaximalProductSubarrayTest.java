import org.junit.*;
import static org.junit.Assert.*;
import java.io.*;

public class MaximalProductSubarrayTest {
  MaximalProductSubarray array = new MaximalProductSubarray();

  @Test
  public void test() throws Exception {
    String s = new BufferedReader(new FileReader(new File("MaximalProductSubarrayTest.input"))).readLine();
    String[] strs = s.split(",");
    int[] numbers = new int[strs.length];
    for (int i = 0; i < strs.length; ++i) {
      numbers[i] = Integer.parseInt(strs[i]);
    }
    assertEquals(1492992000, array.maxProduct(numbers));
  }
}
