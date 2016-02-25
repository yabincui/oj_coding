import java.util.*;

public class WordSearchII {
  char[][] board;

  class Trie {
    int wordIndex;
    Trie parent;
    Trie[] child = new Trie[26];
  }
  boolean[] wordMatched;

  void addWordToTrie(String s, int wordIndex, Trie root) {
    for (int i = 0; i < s.length(); ++i) {
      Trie nt = root.child[s.charAt(i) - 'a'];
      if (nt == null) {
        nt = new Trie();
        nt.parent = root;
        root.child[s.charAt(i) - 'a'] = nt;
      }
      root = nt;
    }
    root.wordIndex = wordIndex;
  }

  Trie removeTrie(Trie t) {
    t.wordIndex = 0;
    for (int i = 0; i < 26; ++i) {
      if (t.child[i] != null) {
        return t;
      }
    }
    while (t.parent != null) {
      Trie p = t.parent;
      boolean hasOtherChild = false;
      for (int i = 0; i < 26; ++i) {
        if (p.child[i] == t) {
          p.child[i] = null;
        } else {
          hasOtherChild = true;
        }
      }
      if (hasOtherChild) {
        return null;
      }
      t = p;
    }
    return null;
  }

  String[] sortAndRemoveDuplication(String[] words) {
    Arrays.sort(words);
    ArrayList<String> wordList = new ArrayList<String>();
    for (int i = 0; i < words.length; ++i) {
      if (i == 0 || words[i].equals(words[i-1]) == false) {
        wordList.add(words[i]);
      }
    }
    return wordList.toArray(new String[0]); 
  }

  public List<String> findWords(char[][] board, String[] words) {
    int m = board.length;
    int n = board[0].length;
    this.board = board;

    // Remove duplication.
    words = sortAndRemoveDuplication(words);
    int wordN = words.length;

    Trie root = new Trie();
    for (int i = 0; i < wordN; ++i) {
      addWordToTrie(words[i], i+1, root);
    }

    wordMatched = new boolean[wordN];

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        matchWordInBoard(i, j, root);
      }
    }
    ArrayList<String> result = new ArrayList<String>();
    for (int i = 0; i < wordN; ++i) {
      if (wordMatched[i]) {
        result.add(words[i]);
      }
    }
    return result;
  }

  void matchWordInBoard(int r, int c, Trie root) {
    if (root == null) {
      return;
    }
    if (board[r][c] == '.') {
      return;
    }
    int index = board[r][c] - 'a';
    if (root.child[index] == null) {
      return;
    }
    root = root.child[index];
    if (root.wordIndex != 0) {
      wordMatched[root.wordIndex-1] = true;
      root = removeTrie(root);
      if (root == null) {
        return;
      }
    }
    board[r][c] = '.';
    if (r > 0) {
      matchWordInBoard(r-1, c, root);
    }
    if (r < board.length - 1) {
      matchWordInBoard(r+1, c, root);
    }
    if (c > 0) {
      matchWordInBoard(r, c-1, root);
    }
    if (c < board[0].length - 1) {
      matchWordInBoard(r, c+1, root);
    }
    board[r][c] = (char)(index + 'a');
  }
}
