import org.junit.*;
import static org.junit.Assert.*;

public class NextPermutationTest {

  private int charToValue(char c) {
    if (c >= '1' && c <= '9') {
      return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
      return c - 'a' + 10;
    }
    return -1;
  }

  private char valueToChar(int value) {
    if (value >= 1 && value <= 9) {
      return (char)(value + '0');
    }
    if (value >= 10 && value <= 15) {
      return (char)(value - 10 + 'a');
    }
    return '?';
  }

  String getNextPermutation(int n, String prev) {
    if (n > 15) {
      return null;
    }
    if (prev == null) {
      char[] buf = new char[n];
      for (int i = 1; i <= n; ++i) {
        buf[i-1] = valueToChar(i);
      }
      return new String(buf);
    }
    int[] values = new int[n];
    for (int i = 0; i < n; ++i) {
      values[i] = charToValue(prev.charAt(i));
    }
    int stop = n - 2;
    for (; stop >= 0; --stop) {
      if (values[stop] < values[stop + 1]) {
        break;
      }
    }
    if (stop < 0) {
      return null;
    }
    int change = stop + 1;
    for (; change + 1 < n && values[change + 1] > values[stop]; ++change) {
    }
    int tmp = values[stop];
    values[stop] = values[change];
    values[change] = tmp;
    for (int i = stop + 1, j = n - 1; i < j; ++i, --j) {
      tmp = values[i];
      values[i] = values[j];
      values[j] = tmp;
    }
    char[] s = new char[n];
    for (int i = 0; i < n; ++i) {
      s[i] = valueToChar(values[i]);
    }
    return new String(s);
  }

  @Test
  public void test() {
    String prev = null;
    int i = 0;
    while (true) {
      String s = getNextPermutation(4, prev);
      if (s == null) {
        break;
      }
      System.out.printf("%d: %s\n", ++i, s);
      prev = s;
    }
  }
}
