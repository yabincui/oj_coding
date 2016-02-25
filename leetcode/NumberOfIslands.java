import java.util.*;

public class NumberOfIslands {
  class Node {
    int r, c;
    Node() {
      r = c = 0;
    }
    Node(int row, int col) {
      r = row;
      c = col;
    }
  }
  public int numIslands(char[][] grid) {
    int count = 0;
    for (int i = 0; i < grid.length; ++i) {
      for (int j = 0; j < grid[i].length; ++j) {
        if (grid[i][j] == '1') {
          ++count;
          removeIsland(grid, i, j);
        }
      }
    }
    return count;
  }

  void removeIsland(char[][] grid, int r, int c) {
    ArrayDeque<Node> queue = new ArrayDeque<Node>();
    Node node = new Node();
    node.r = r;
    node.c = c;
    queue.add(node);
    while (!queue.isEmpty()) {
      node = queue.poll();
      r = node.r;
      c = node.c;
      if (r >= 0 && r < grid.length && c >= 0 && c < grid[r].length && grid[r][c] == '1') {
        grid[r][c] = 0;
        queue.add(new Node(r-1, c));
        queue.add(new Node(r+1, c));
        queue.add(new Node(r, c-1));
        queue.add(new Node(r, c+1));
      }
    }
  }
}
