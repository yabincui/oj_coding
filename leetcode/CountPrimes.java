import java.util.*;

public class CountPrimes {
  public int countPrimes(int n) {
    ArrayList<Integer> primes = new ArrayList<Integer>();
    for (int i = 3; i < n; i += 2) {
      boolean valid = true;
      for (Integer p : primes) {
        if (i % p == 0) {
          valid = false;
          break;
        }
      }
      if (valid) {
        primes.add(i);
      }
    }
    if (n >= 2) {
      primes.add(2);
    }
    return primes.size();
  }
  
  public int countPrimes(int n) {
    boolean[] s = new boolean[n + 1];
    int count = (n > 2 ? 1 : 0);
    for (int i = 3; i < n; i += 2) {
      if (!s[i]) {
        count++;
        for (int j = i + i; j < n; j += i) {
          s[j] = true;
        }
      }
    }
    return count;
  }

}
