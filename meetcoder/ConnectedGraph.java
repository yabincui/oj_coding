import java.util.*;

public class ConnectedGraph {
  public int connectThem0(int n) {
    int maxDay = (n - 1) * (n - 2) + 1;
    // dp[i][j] means the probability of connecting i cities exactly in j days.
    double[][] dp = new double[n + 1][maxDay + 1];

    dp[0][0] = 1;
    dp[1][0] = 1;
    for (int i = 2; i <= n; ++i) {
      double accPro = 0;
      int prevRoadNum = (i - 1) * (i - 2) / 2;
      for (int j = 1; j <= prevRoadNum + 1; ++j) {
        double pro = accPro + dp[i - 1][j - 1];
        int expectedRoadNum = i - 1;
        int totalRoadNum = prevRoadNum - (j - 1) + (i - 1);
        double temp = (double)expectedRoadNum / totalRoadNum;
        dp[i][j] = pro * temp;
        //System.out.printf("dp[%d][%d] = %f\n", i, j, dp[i][j]);
        accPro = pro * (1 - temp);
      }
    }
    double expectedDays = 0;
    for (int j = 0; j <= maxDay; ++j) {
      expectedDays += j * dp[n][j];
    }
    System.out.printf("n = %d, expectedDays = %f\n", n, expectedDays);
    int result = (int)Math.ceil(expectedDays);
    return result;
  }

  public int connectThem1(int n) {
    int[] dp = new int[n + 1];
    dp[0] = 0;
    dp[1] = 0;
    for (int i = 2; i <= n; ++i) {
      double remDays = (i - 1) * (i - 2) / 2 - dp[i - 1] + (i - 1);
      double expectedDays = (i - 1);
      double p = expectedDays / remDays;
      double add = 1 / p;
      dp[i] = (int)Math.floor(dp[i - 1] + add);
    }
    System.out.printf("dp[%d] = %d\n", n, dp[n]);
    return (int)Math.ceil(dp[n]);
  }

  class Node {
    // s[i] means the count of connected parts in size i.
    int[] s = new int[31];
  }

  class NodeComparator implements Comparator<Node> {
    public int compare(Node n1, Node n2) {
      for (int i = 0; i < n1.s.length; ++i) {
        if (n1.s[i] != n2.s[i]) {
          return n1.s[i] - n2.s[i];
        }
      }
      return 0;
    }
  }

  public int connectThem(int n) {
    if (n <= 1) {
      return 0;
    }
    // dp[i] represents all the situations in day i.
    // Each node in the tree represents a possible situation in day i.
    ArrayList<TreeMap<Node, Double>> dp = new ArrayList<TreeMap<Node, Double>>();
    Node node = new Node();
    node.s[1] = n;
    NodeComparator comparator = new NodeComparator();
    TreeMap<Node, Double> map = new TreeMap<Node, Double>(comparator);
    map.put(node, 1.0);
    dp.add(map);

    Node searchNode = new Node();
    searchNode.s[n] = 1;

    double expectedDays = 0.0;

    for (int i = 0; i < dp.size(); ++i) {
      map = dp.get(i);
      TreeMap<Node, Double> nextMap = new TreeMap<Node, Double>(comparator);
      int existRoad = i;
      for (Node n1 : map.keySet()) {
        double curPro = map.get(n1);
        // the max roads can contains if keeping current connected parts unchanged.
        int curMaxRoad = getCurMaxRoad(n1);

        int oldConnectRoad = curMaxRoad - existRoad;

        // possible roads that can connect two parts. 
        int newConnectRoad = n * (n - 1) / 2 - curMaxRoad;
        
        int possibleRoad = oldConnectRoad + newConnectRoad;

        if (oldConnectRoad != 0) {
          addPossible(nextMap, n1, curPro * oldConnectRoad / possibleRoad);
        }
        int addRoad = 0;
        for (int j = 1; j < 30; ++j) {
          if (n1.s[j] == 0) {
            continue;
          }
          int count1 = n1.s[j];
          n1.s[j]--;
          if (n1.s[j] >= 1) {
            int connectRoad = count1 * (count1 - 1) / 2 * j * j;
            n1.s[j]--;
            n1.s[j+j]++;
            addPossible(nextMap, n1, curPro * connectRoad / possibleRoad);
            n1.s[j]++;
            n1.s[j+j]--;
            addRoad += connectRoad;
          }
          for (int k = j + 1; k < 30; ++k) {
            if (n1.s[k] == 0) {
              continue;
            }
            int connectRoad = count1 * n1.s[k] * j * k;
            n1.s[k]--;
            n1.s[j+k]++;
            addPossible(nextMap, n1, curPro * connectRoad / possibleRoad);
            n1.s[k]++;
            n1.s[j+k]--;
            addRoad += connectRoad;
          }
          n1.s[j]++;
        }
        if (addRoad != newConnectRoad) {
          return -1;
        }
      }

      Double value = nextMap.get(searchNode);
      if (value != null) {
        expectedDays += value * (i + 1);
        nextMap.remove(searchNode);
      }
      if (nextMap.size() > 0) {
        dp.add(nextMap);
      }
    }
    return (int)Math.floor(expectedDays);
  }

  void addPossible(TreeMap<Node, Double> map, Node n, double pro) {
    Node newNode = new Node();
    for (int i = 1; i < n.s.length; ++i) {
      newNode.s[i] = n.s[i];
    }
    Double oldValue = map.get(newNode);
    if (oldValue != null) {
      pro += oldValue;
    }
    map.put(newNode, pro);
  }

  int getCurMaxRoad(Node n) {
    int road = 0;
    for (int i = 1; i < n.s.length; ++i) {
      road += n.s[i] * i * (i - 1) / 2;
    }
    return road;
  }
}
