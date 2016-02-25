public class BitwiseAndOfNumbersRange {
  public int rangeBitwiseAnd(int m, int n) {
    int value = 0;
    for (int i = 30; i >= 0; --i) {
      int mask = (1 << i);
      int mid = value + mask;
      if (n < mid) {
        continue;
      } else if (m >= mid) {
        value = mid;
      } else {
        break;
      }
    }
    return value;
  }
}
