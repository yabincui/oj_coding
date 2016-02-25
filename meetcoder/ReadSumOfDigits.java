public class ReadSumOfDigits {
  public String readSum(String n) {
    int sum = 0;
    for (int i = 0; i < n.length(); ++i) {
      sum += n.charAt(i) - '0';
    }
    String[] digitMap = new String[] {
      "zero", "one", "two", "three", "four", "five", "six", "seven",
      "eight", "nine"
    };
    int level = 1;
    for (; level <= sum; level *= 10) {
    }
    level /= 10;
    if (level == 0) {
      level = 1;
    }
    StringBuilder builder = new StringBuilder();
    for (; level > 0; level /= 10) {
      int digit = sum / level % 10;
      if (builder.length() != 0) {
        builder.append(" ");
      }
      builder.append(digitMap[digit]);
    }
    return builder.toString();
  }
}
