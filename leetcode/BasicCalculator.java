import java.util.*;

public class BasicCalculator {
  class Node {
    boolean isOp;
    char op;
    int value;
  }
  public int calculate(String s) {
    ArrayList<Node> queue = new ArrayList<Node>();
    ArrayList<Character> opQueue = new ArrayList<Character>();
    for (int i = 0; i < s.length(); ++i) {
      if (s.charAt(i) >= '0' && s.charAt(i) <= '9') {
        int value = s.charAt(i) - '0';
        for (i += 1; i < s.length() && s.charAt(i) >= '0' && s.charAt(i) <= '9'; ++i) {
          value = value * 10 + s.charAt(i) - '0';
        }
        --i;
        Node node = new Node();
        node.isOp = false;
        node.value = value;
        queue.add(node);
      } else if (s.charAt(i) == '+' || s.charAt(i) == '-') {
        while (opQueue.isEmpty() == false) {
          char op = opQueue.get(opQueue.size() - 1);
          if (op == '+' || op == '-') {
            Node node = new Node();
            node.isOp = true;
            node.op = op;
            queue.add(node);
            opQueue.remove(opQueue.size() - 1);
          } else {
            break;
          }
        }
        opQueue.add(s.charAt(i));
      } else if (s.charAt(i) == '(') {
        opQueue.add(s.charAt(i));
      } else if (s.charAt(i) == ')') {
        while (opQueue.isEmpty() == false) {
          char op = opQueue.get(opQueue.size() - 1);
          if (op == '+' || op == '-') {
            Node node = new Node();
            node.isOp = true;
            node.op = op;
            queue.add(node);
            opQueue.remove(opQueue.size() - 1);
          } else if (op == '(') {
            opQueue.remove(opQueue.size() - 1);
            break;
          }
        }
      }
    }
    if (opQueue.isEmpty() == false) {
      Node node = new Node();
      node.isOp = true;
      node.op = opQueue.get(opQueue.size() - 1);
      queue.add(node);
    }
    ArrayList<Integer> valueQueue = new ArrayList<Integer>();
    for (int i = 0; i < queue.size(); ++i) {
      Node node = queue.get(i);
      if (node.isOp == false) {
        valueQueue.add(node.value);
      } else if (node.op == '+' || node.op == '-') {
        int value2 = valueQueue.get(valueQueue.size() - 1);
        valueQueue.remove(valueQueue.size() - 1);
        int value1 = valueQueue.get(valueQueue.size() - 1);
        valueQueue.remove(valueQueue.size() - 1);
        if (node.op == '+') {
          valueQueue.add(value1 + value2);
        } else {
          valueQueue.add(value1 - value2);
        }
      }
    }
    return valueQueue.get(0);
  }
}
