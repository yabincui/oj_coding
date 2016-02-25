import java.util.*;

public class MinStack {
  public void push(int x) {
    stack.add(x);
    if (minPosStack.isEmpty() || stack.get(minPosStack.get(minPosStack.size() - 1)) > x) {
      minPosStack.add(stack.size() - 1);
    }
  }

  public void pop() {
    stack.remove(stack.size() - 1);
    if (minPosStack.get(minPosStack.size() - 1) == stack.size()) {
      minPosStack.remove(minPosStack.size() - 1);
    }
  }

  public int top() {
    return stack.get(stack.size() - 1);
  }

  public int getMin() {
    return stack.get(minPosStack.get(minPosStack.size() - 1));
  }

  ArrayList<Integer> stack = new ArrayList<Integer>();
  ArrayList<Integer> minPosStack = new ArrayList<Integer>();
}
