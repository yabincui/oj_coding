public class FactorialTrailingZeroes {
  public int trailingZeroes(int n) {
    long two = 0;
    long five = 0;

    long p = 2;
    while (p <= n) {
      two += n / p;
      p *= 2;
    }

    p = 5;
    while (p <= n) {
      five += n / p;
      p *= 5;
    }

    return (int)Math.min(two, five);
  }
}
