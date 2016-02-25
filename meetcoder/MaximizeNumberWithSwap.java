public class MaximizeNumberWithSwap {
  public int maximizeResult(int n) {
    long value = n;
    int maxDigit = -1;
    long maxDigitLevel = 0;
    long level = 1;
    long result = value;
    for (; level <= value; level *= 10) {
      int digit = (int)(value / level % 10);
      if (digit < maxDigit) {
        long add = (maxDigit - digit) * level - (maxDigit - digit) * maxDigitLevel;
        result = value + add;
      } else if (digit > maxDigit) {
        maxDigit = digit;
        maxDigitLevel = level;
      }
    }
    return (int)result;
  }
}
