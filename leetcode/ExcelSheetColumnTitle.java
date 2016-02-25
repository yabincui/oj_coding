public class ExcelSheetColumnTitle {
  public String convertToTitle(int n) {
    StringBuilder builder = new StringBuilder();
    while (true) {
      n--;
      builder.append((char)(n % 26 + 'A'));
      n /= 26;
      if (n == 0) {
        break;
      }
    }
    return builder.reverse().toString();
  }
}
