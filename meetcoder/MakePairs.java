import java.util.*;

public class MakePairs {
  public boolean makePair(int[] a, int[] b, int k) {
    Arrays.sort(a);
    Arrays.sort(b);
    for (int i = 0; i < a.length; ++i) {
      int j = a.length - 1 - i;
      if (a[i] + b[j] < k) {
        return false;
      }
    }
    return true;
  }
}
