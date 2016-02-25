import java.util.*;

public class FractionToRecurringDecimal {
  public String fractionToDecimal(int numerator1, int denominator1) {
    boolean negative = false;
    long numerator = numerator1;
    long denominator = denominator1;
    if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0)) {
      negative = true;
      if (numerator < 0) {
        numerator = - numerator;
      }
      if (denominator < 0) {
        denominator = -denominator;
      }
    }
    HashMap<Long, Integer>  posMap = new HashMap<Long, Integer>();
    StringBuilder builder = new StringBuilder();
    if (negative) {
      builder.append("-");
    }
    builder.append(numerator / denominator);
    numerator %= denominator;
    if (numerator != 0) {
      builder.append('.');
    }
    while (numerator != 0) {
      numerator *= 10;
      Integer pos = posMap.get(numerator);
      if (pos == null) {
        builder.append(numerator / denominator);
        posMap.put(numerator, builder.length() - 1);
        numerator %= denominator;
      } else {
        builder.insert(pos, "(");
        builder.append(')');
        break;
      }
    }
    return builder.toString();
  }
}
