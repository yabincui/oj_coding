import java.util.*;

public class BSTIterator {
  public BSTIterator(TreeNode root) {
    stack = new Stack<TreeNode>();
    while (root != null) {
      stack.push(root);
      root = root.left;
    }
  }

  public boolean hasNext() {
    return !stack.isEmpty();
  }

  public int next() {
    TreeNode cur = stack.pop();
    TreeNode node = cur.right;
    while (node != null) {
      stack.push(node);
      node = node.left;
    }
    return cur.val;
  }

  Stack<TreeNode> stack;
}
