import java.util.*;

public class ContainsDuplicateII {

  class Node {
    int value;
    int pos;
  }
  class NodeComparator implements Comparator<Node> {
    public int compare(Node n1, Node n2) {
      if (n1.value != n2.value) {
        return n1.value - n2.value;
      }
      return n1.pos - n2.pos;
    }
  }
  public boolean containsNearbyDuplicate(int[] nums, int k) {
    Node[] nodes = new Node[nums.length];
    for (int i = 0; i < nums.length; ++i) {
      Node node = new Node();
      node.value = nums[i];
      node.pos = i;
      nodes[i] = node;
    }
    Arrays.sort(nodes, new NodeComparator());
    for (int i = 1; i < nodes.length; ++i) {
      if (nodes[i-1].value == nodes[i].value && nodes[i].pos - nodes[i-1].pos <= k) {
        return true;
      }
    }
    return false;
  }
}
