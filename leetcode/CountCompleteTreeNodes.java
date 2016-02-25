public class CountCompleteTreeNodes {
  public int countNodes(TreeNode root) {
    if (root == null) {
      return 0;
    }
    int h = 0;
    TreeNode node = root;
    while (node.left != null) {
      node = node.left;
      h++;
    }
    long count = 0;
    long level = 1;
    for (int i = 0; i < h; ++i) {
      count += level;
      level *= 2;
    }
    long low = 1;
    long high = level;
    while (low + 1 < high) {
      long mid = (low + high) / 2;
      if (access(mid, root, h, level / 2)) {
        low = mid;
      } else {
        high = mid - 1;
      }
    }
    long add = low;
    if (low + 1 == high && access(low + 1, root, h, level / 2)) {
      add = low + 1;
    }
    return (int)(count + add);
  }

  boolean access(long value, TreeNode root, int h, long level) {
    for (int i = 0; i < h; ++i) {
      if (value <= level) {
        root = root.left;
      } else {
        root = root.right;
        value -= level;
      }
      level /= 2;
    }
    return (root != null);
  }
}
