import java.util.*;

public class CountOfSmallerNumbersAfterSelf {

  class Node {
    int max_value;
    int count;
    Node left, right;

    Node() {
      max_value = Integer.MIN_VALUE;
      count = 0;
      left = null;
      right = null;
    }

    Node(int value) {
      max_value = value;
      count = 1;
      left = right = null;
    }
  }

  private Node addValue(Node root, int l, int r, int value) {
    if (l == r) {
      if (l == value) {
        if (root == null) {
          root = new Node(value);
        } else {
          root.count++;
        }
      }
    } else {
      if (root == null) {
        root = new Node();
      }
      int mid = (l + r) / 2;
      if (l + 1 == r && mid == r) {
        mid = l;
      }
      if (value <= mid) {
        root.left = addValue(root.left, l, mid, value);
      } else {
        root.right = addValue(root.right, mid + 1, r, value);
      }
      root.max_value = Integer.max(root.max_value, value);
      root.count++;
    }
    return root;
  }

  private int getSmallerCount(Node root, int l, int r, int value) {
    if (root == null || l >= value) {
      return 0;
    }
    if (r < value) {
      return root.count;
    }
    int mid = (l + r) / 2;
    if (l + 1 == r && mid == r) {
      mid = l;
    }
    int sum = 0;
    if (value > l) {
      sum += getSmallerCount(root.left, l, mid, value);
    }
    if (value > mid + 1) {
      sum += getSmallerCount(root.right, mid + 1, r, value);
    }
    return sum;
  }

  public List<Integer> countSmaller(int[] nums) {
    int[] res = new int[nums.length];
    Node root = null;
    int min_value = Integer.MAX_VALUE;
    int max_value = Integer.MIN_VALUE;
    for (int i = 0; i < nums.length; ++i) {
      min_value = Integer.min(min_value, nums[i]);
      max_value = Integer.max(max_value, nums[i]);
    }
    for (int i = nums.length - 1; i >= 0; --i) {
      int c = getSmallerCount(root, min_value, max_value, nums[i]);
      res[i] = c;
      root = addValue(root, min_value, max_value, nums[i]);
    }

    ArrayList<Integer> result = new ArrayList<Integer>();
    for (int i = 0; i < nums.length; ++i) {
      result.add(res[i]);
    }
    return result;
  }

  public static void main(String[] args) {
    //int[] nums = new int[]{5, 2, 6, 1};
    int[] nums = new int[]{-1, -2, -2};
    
    CountOfSmallerNumbersAfterSelf obj = new CountOfSmallerNumbersAfterSelf();
    List<Integer> res = obj.countSmaller(nums);
    for (int i = 0; i < res.size(); ++i) {
      System.out.printf("%d ", res.get(i));
    }
    System.out.printf("\n");
  }
}
