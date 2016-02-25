public class ExcelSheetColumnNumber {
  public int titleToNumber(String s) {
    int value = 0;
    for (int i = 0; i < s.length(); ++i) {
      value = value * 26 + (s.charAt(i) - 'A' + 1);
    }
    return value;
  }
}
