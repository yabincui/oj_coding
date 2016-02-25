import java.util.*;

public class BinaryTreeRightSideView {
  public List<Integer> rightSideView(TreeNode root) {
    ArrayList<Integer> result = new ArrayList<Integer>();
    viewTree(root, 0, result);
    return result;
  }

  void viewTree(TreeNode root, int depth, ArrayList<Integer> result) {
    if (root == null) {
      return;
    }
    if (result.size() == depth) {
      result.add(root.val);
    }
    viewTree(root.right, depth + 1, result);
    viewTree(root.left, depth + 1, result);
  }
}
