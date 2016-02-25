import java.util.*;

public class Temp {
    // Implementation 1: Accept
    public List<List<Integer>> combinationSum3(int k, int n) {
        ArrayList<Integer> item = new ArrayList<Integer>();
        List<List<Integer>> result = new ArrayList<List<Integer>>();
        recur(1, k, n, result, item);
        return result;
    }
    
    private void recur(int start, int k, int n, List<List<Integer>> result, ArrayList<Integer> item) {
        if (k == 0) {
            if (n == 0)
                result.add((List<Integer>) item.clone());
            return;
        }
        for (int i = start; i <= 9; i++) {
            item.add(i);
            recur(i + 1, k - 1, n - i, result, item);
            item.remove(item.size() - 1);
        }
    }

    // Implementation 2: Compiler Error
    public ArrayList<ArrayList<Integer>> combinationSum32(int k, int n) {
        ArrayList<Integer> item = new ArrayList<Integer>();
        ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>>();
        recur(1, k, n, result, item);
        return result;
    }
    
    private void recur(int start, int k, int n, ArrayList<ArrayList<Integer>> result, ArrayList<Integer> item) {
        if (k == 0) {
            if (n == 0)
                result.add((ArrayList<Integer>) item.clone());
            return;
        }
        for (int i = start; i <= 9; i++) {
            item.add(i);
            recur(i + 1, k - 1, n - i, result, item);
            item.remove(item.size() - 1);
        }
    }
}
