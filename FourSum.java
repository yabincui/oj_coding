// Give a list of numbers, and a target number. Return true if we can find 4 numbers
// in the list that sum up to the target number.

import java.util.*;
import org.junit.*;
import static org.junit.Assert.*;

public class FourSum {
  class Node {
    int minPos;
    int value;
    Node(int minPos, int value) {
      this.minPos = minPos;
      this.value = value;
    }
  }

  class NodeComparator implements Comparator<Node> {
    public int compare(Node n1, Node n2) {
      if (n1.value != n2.value) {
        return n1.value - n2.value;
      }
      return n1.minPos - n2.minPos;
    }
  }

  public boolean fourSum(int[] s, int target) {
    if (s == null || s.length < 4) {
      return false;
    }
    int n = s.length;
    Node[] t = new Node[n * (n - 1) / 2];
    int k = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        t[k++] = new Node(i, s[i] + s[j]);
      }
    }
    Arrays.sort(t, new NodeComparator());
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (bsearch(t, target - s[i] - s[j], j + 1)) {
          return true;
        }
      }
    }
    return false;
  }

  private boolean bsearch(Node[] t, int value, int minPos) {
    int low = 0;
    int high = t.length - 1;
    while (low <= high) {
      int mid = (low + high) / 2;
      if (t[mid].value < value || (t[mid].value == value && t[mid].minPos < minPos)) {
        low = mid + 1;
      } else if (t[mid].value == value) {
        return true;
      } else {
        high = mid - 1;
      }
    }
    return false;
  }

  @Test
  public void test() {
    FourSum sum = new FourSum();
    assertTrue(sum.fourSum(new int[]{1, 2, 3, 4}, 10));
    assertTrue(sum.fourSum(new int[]{1, 1, 1, 1}, 4));
    assertFalse(sum.fourSum(new int[]{2, 3, 2, 2}, 10));
  }
}
