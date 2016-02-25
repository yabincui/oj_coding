public class StringCompression {
  public String compressString(String str) {
    StringBuilder builder = new StringBuilder();
    char c = 0;
    int count = 0;
    for (int i = 0; i < str.length(); ++i) {
      if (c != str.charAt(i)) {
        if (count != 0) {
          builder.append(c);
          builder.append(count);
        }
        count = 1;
        c = str.charAt(i);
      } else {
        ++count;
      }
    }
    if (count != 0) {
      builder.append(c);
      builder.append(count);
    }
    String result = builder.toString();
    if (result.length() >= str.length()) {
      result = str;
    }
    return result;
  }
}
