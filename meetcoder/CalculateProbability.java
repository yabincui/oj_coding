public class CalculateProbability {
  public int[] calculate(int a, int b, int c) {
    int numerator = 0;
    int denominator = a * b * 2;

    if (a < b) {
      int temp = a;
      a = b;
      b = temp;
    }
    if (c >= a + b) {
      numerator = a * b * 2;
    } else if (c >= a) {
      numerator = c * c - (c - b) * (c - b) - (c - a) * (c - a);
    } else if (c >= b) {
      numerator = c * c - (c - b) * (c - b);
    } else {
      numerator = c * c;
    }
    int factor = gcd(numerator, denominator);
    int[] result = new int[2];
    result[0] = numerator / factor;
    result[1] = denominator / factor;
    return result;
  }

  int gcd(int a, int b) {
    if (a < b) {
      int temp = a;
      a = b;
      b = temp;
    }
    int c = a % b;
    while (c != 0) {
      a = b;
      b = c;
      c = a % b;
    }
    return b;
  }
}
