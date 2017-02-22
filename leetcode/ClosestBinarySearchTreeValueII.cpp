// 272 Closest Binary Search Tree Value II
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public List<Integer> closestKValues(TreeNode root, double target, int k) {
        Deque<TreeNode> leftS = new ArrayDeque<TreeNode>();
        Deque<TreeNode> rightS = new ArrayDeque<TreeNode>();
        findNearest(root, target, leftS, true);
        findNearest(root, target, rightS, false);
        List<Integer> res = new ArrayList<Integer>();
        while (res.size() < k) {
            boolean use_left = false;
            boolean use_right = false;
            if (leftS.isEmpty()) {
                use_right = true;
            } else if (rightS.isEmpty()) {
                use_left = true;
            } else if (leftS.peek().val == rightS.peek().val) {
                use_left = use_right = true;
            } else if (target - leftS.peek().val < rightS.peek().val - target) {
                use_left = true;
            } else {
                use_right = true;
            }
            res.add(use_left ? leftS.peek().val : rightS.peek().val);
            if (use_left) {
                TreeNode node = leftS.pop();
                node = node.left;
                while (node != null) {
                    leftS.push(node);
                    node = node.right;
                }
                while (!leftS.isEmpty() && leftS.peek().val > target) {
                    leftS.pop();
                }
            }
            if (use_right) {
                TreeNode node = rightS.pop();
                node = node.right;
                while (node != null) {
                    rightS.push(node);
                    node = node.left;
                }
                while (!rightS.isEmpty() && rightS.peek().val < target) {
                    rightS.pop();
                }
            }
        }
        return res;
    }
    
    void findNearest(TreeNode root, double target, Deque<TreeNode> s, boolean fromLeft) {
        while (root != null) {
            s.push(root);
            //System.out.printf("fromLeft = %b, push %d\n", fromLeft, root.val);
            if (root.val == target) {
                break;
            }
            if (root.val < target) {
                root = root.right;
            } else {
                root = root.left;
            }
        }
        if (fromLeft) {
            while (!s.isEmpty() && s.peek().val > target) {
                //System.out.printf("pop %d\n", s.peek().val);
                s.pop();
            }
        } else {
            while (!s.isEmpty() && s.peek().val < target) {
                //System.out.printf("pop %d\n", s.peek().val);
                s.pop();
            }
        }
    }
}
