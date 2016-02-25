import java.util.*;

public class HappyNumber {
  public boolean isHappy(int n) {
    HashSet<Integer> set = new HashSet<Integer>();
    while (n != 1) {
      if (set.contains(n)) {
        return false;
      }
      set.add(n);
      int value = 0;
      while (n != 0) {
        value += (n % 10) * (n % 10);
        n /= 10;
      }
      n = value;
    }
    return true;
  }
}
