import org.junit.*;
import static org.junit.Assert.*;
import java.util.ArrayList;
import java.io.*;

public class BestTimeToBuyAndSellStockIVTest {
  BestTimeToBuyAndSellStockIV stock = new BestTimeToBuyAndSellStockIV();
  @Test
  public void test1() throws FileNotFoundException, IOException {
    ArrayList<Integer> nums = new ArrayList<Integer>();
    File file = new File("stock.in");
    BufferedReader in = new BufferedReader(new FileReader(file));
    String s = in.readLine();
    while (s != null) {
      nums.add(Integer.parseInt(s));
      s = in.readLine();
    }
    int[] array = new int[nums.size()];
    for (int i = 0; i < nums.size(); ++i) {
      array[i] = nums.get(i);
    }

    int result = stock.maxProfit(1000000000, array);
    System.out.println("result = " + result);
  }
} 
