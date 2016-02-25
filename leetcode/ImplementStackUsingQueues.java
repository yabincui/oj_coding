import java.util.*;

class MyStack {
  public void push(int x) {
    int oldSize = queue.size();
    queue.add(x);
    for (int i = 0; i < oldSize; ++i) {
      int value = queue.remove(0);
      queue.add(value);
    }
  }

  public void pop() {
    queue.remove(0); 
  }

  public int top() {
    return queue.get(0);
  }

  public boolean empty() {
    return queue.isEmpty();
  }

  ArrayList<Integer> queue = new ArrayList<Integer>();

}

public class ImplementStackUsingQueues {
}
