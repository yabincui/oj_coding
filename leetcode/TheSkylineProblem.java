import java.util.*;

public class TheSkylineProblem {
  class Node {
    boolean isStart;
    int x;
    int h;
  }

  class NodeComparator implements Comparator<Node> {
    public int compare(Node n1, Node n2) {
      if (n1.x != n2.x) {
        return n1.x - n2.x;
      }
      if (n1.isStart != n2.isStart) {
        return n1.isStart ? -1 : 1;
      }
      if (n1.isStart) {
        return n2.h - n1.h;
      }
      return n1.h - n2.h;
    }
  }

  public List<int[]> getSkyline(int[][] buildings) {
    int n = buildings.length;
    ArrayList<Node> s = new ArrayList<Node>();
    for (int i = 0; i < n; ++i) {
      Node node = new Node();
      node.isStart = true;
      node.x = buildings[i][0];
      node.h = buildings[i][2];
      s.add(node);
      node = new Node();
      node.isStart = false;
      node.x = buildings[i][1];
      node.h = buildings[i][2];
      s.add(node);
    }
    Collections.sort(s, new NodeComparator());

    TreeMap<Integer, Integer> height_map = new TreeMap<Integer, Integer>();
    ArrayList<int[]> result = new ArrayList<int[]>();
    int beginX = 0;
    int curH = 0;
    for (int i = 0; i < s.size(); ++i) {
      Node node = s.get(i);
      if (node.isStart) {
        Integer old = height_map.get(node.h);
        int newValue = 1;
        if (old != null) {
          newValue += old;
        }
        height_map.put(node.h, newValue);
        if (node.h > curH) {
          beginX = node.x;
          curH = node.h;
          result.add(new int[]{beginX, curH});
        }
      } else {
        Integer old = height_map.get(node.h);
        if (old == 1) {
          height_map.remove(node.h);
        } else {
          height_map.put(node.h, old - 1);
        }
        if (height_map.size() == 0) {
          beginX = node.x;
          curH = 0;
          result.add(new int[]{beginX, curH});
        } else {
          Integer h = (int)height_map.lastKey();
          if (h != curH) {
            beginX = node.x;
            curH = h;
            result.add(new int[]{beginX, curH});
          }
        }
      }
    }
    return result;
  }
}
