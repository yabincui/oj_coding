import java.util.*;

public class MaximalRectangle {
  public int maximalRectangle(char[][] matrix) {
    if (matrix.length == 0 || matrix[0].length == 0) {
      return 0;
    }
    int m = matrix.length;
    int n = matrix[0].length;
    int[][] height = new int[m][n];

    // Init height information.
    for (int i = 0; i < n; ++i) {
      if (matrix[0][i] == '1') {
        height[0][i] = 1;
      }
    }
    for (int i = 1; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == '1') {
          height[i][j] = height[i - 1][j] + 1;
        } else {
          height[i][j] = 0;
        }
      }
    }

    int maxArea = 0;
    // Loop each row, using it as the bottom line.
    for (int i = 0; i < m; ++i) {
      int temp = maxAreaOfLine(height[i]);
      maxArea = Math.max(maxArea, temp);
    }
    return maxArea;
  }

  class Item {
    int index;
    int h;
  }

  class CompareItem implements Comparator<Item> {
    public int compare(Item t1, Item t2) {
      if (t1.h != t2.h) {
        return t1.h - t2.h;
      }
      return t1.index - t2.index;
    }
  }

  class Range {
    int start;
    int end;
  }

  class CompareRange implements Comparator<Range> {
    public int compare(Range r1, Range r2) {
      return r1.start - r2.start;
    }
  }

  public int maxAreaOfLine(int[] height) {
    int n = height.length;
    Item[] items = new Item[n];
    for (int i = 0; i < n; ++i) {
      Item item = new Item();
      item.index = i;
      item.h = height[i];
      items[i] = item;
    }
    Arrays.sort(items, new CompareItem());
    TreeSet<Range> ranges = new TreeSet<Range>(new CompareRange()); 
    Range range = new Range();
    range.start = 0;
    range.end = n - 1;
    ranges.add(range);
    int maxArea = 0;
    // Delete each item in order.
    for (int i = 0; i < n; ++i) {
      Range r = new Range();
      r.start = items[i].index;
      r = ranges.floor(r);
      int tempArea = (r.end - r.start + 1) * items[i].h;
      maxArea = Math.max(maxArea, tempArea);
      ranges.remove(r);
      Range r1 = new Range();
      r1.start = r.start;
      r1.end = items[i].index - 1;
      if (r1.start <= r1.end) {
        ranges.add(r1);
      }
      Range r2 = new Range();
      r2.start = items[i].index + 1;
      r2.end = r.end;
      if (r2.start <= r2.end) {
        ranges.add(r2);
      }
    }
    return maxArea;
  }
}
