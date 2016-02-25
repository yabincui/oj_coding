import java.util.*;

public class CoverTheMagicBoard {
  final long MOD = 10000007;
  public int coverBoard0(int N, int M) {
    if (M == 0) {
      return 0;
    }

    int maxState = (1 << M) - 1;
    // dp[i][j] means the number of ways to achieve state j in row i.
    // state j, for each bit k, if (j & (1 << k)), column k is covered, otherwith column k is not covered.
    int[][] dp = new int[N][maxState + 1];
    for (int i = 0; i <= maxState; ++i) {
      dp[0][i] = 1;
    }
    for (int i = 1; i < N; ++i) {
      permuteState(dp, i, 0, 0, 0, M);
    }
    return dp[N - 1][maxState];
  }

  void permuteState(int[][] dp, int curRow, int curCol, int targetState, int prevState, int M) {
    if (curCol == M) {
      dp[curRow][targetState] = (int)((dp[curRow][targetState] + dp[curRow - 1][prevState]) % MOD);
      return;
    }
    // Don't cover (curRow, curCol).
    permuteState(dp, curRow, curCol + 1, targetState, prevState | (1 << curCol), M);
    // Cover (curRow, curCol) with 1 * 1.
    permuteState(dp, curRow, curCol + 1, targetState | (1 << curCol), prevState | (1 << curCol), M);
    // Cover (curRow, curCol) with 2 * 2.
    if (curCol < M - 1) {
      permuteState(dp, curRow, curCol + 2, targetState | (3 << curCol), prevState, M);
    }
  }

  public int coverBoard(int N, int M) {
    if (M == 0) {
      return 0;
    }

    int maxState = (1 << M) - 1;
    long[][] nearDown = new long[maxState + 1][maxState + 1];
    for (int i = 0; i <= maxState; ++i) {
      for (int j = 0; j <= maxState; ++j) {
        long[] count = new long[M + 1];
        count[0] = 1;
        int pa = 1;
        int pb = 0;
        for (int k = 1; k <= M; ++k) {
          int a = (i >> (k - 1)) & 1;
          int b = (j >> (k - 1)) & 1;
          if (a == 0) {
            if (b == 0) {
              count[k] = (count[k] + count[k - 1]) % MOD;
            } else if (b == 1) {
              count[k] = (count[k] + count[k - 1]) % MOD;
              if (pa == 0 && pb == 1) {
                count[k] = (count[k] + count[k - 2]) % MOD;
              }
            }
          } else if (a == 1) {
            count[k] = (count[k] + count[k - 1]) % MOD;
          }
          pa = a;
          pb = b;
        }
        nearDown[i][j] = count[M];
      }
    }

    ArrayList<int[]> interact = new ArrayList<int[]>();
    permuteInteract(0, 0, 0, M, interact);

    int interactNum = interact.size();
    long[][][] dp = new long[32][interactNum][interactNum];

    for (int i = 0; i < interactNum; ++i) {
      for (int j = 0; j < interactNum; ++j) {
        // From below i to above j.
        int belowState = interact.get(i)[1];
        int aboveState = interact.get(j)[0];
        dp[1][i][j] = nearDown[belowState][aboveState];
      }
    }
    for (int p = 2; p <= 31; ++p) {
      for (int i = 0; i < interactNum; ++i) {
        for (int j = 0; j < interactNum; ++j) {
          for (int k = 0; k < interactNum; ++k) {
            // From below i to above j, go through above k and below k.
            dp[p][i][j] = (dp[p][i][j] + dp[p-1][i][k] * dp[p-1][k][j]) % MOD;
          }
        }
      }
    }
    long[] cur = new long[interactNum];
    for (int i = 0; i < interactNum; ++i) {
      int aboveState = interact.get(i)[0];
      cur[i] = nearDown[maxState][aboveState];
    }
    int last = N - 1;
    for (int p = 1; (1L << p) <= last; ++p) {
      if ((last & (1 << p)) == 0) {
        continue;
      }
      long[] next = new long[interactNum];
      for (int i = 0; i < interactNum; ++i) {
        for (int j = 0; j < interactNum; ++j) {
          // cur[i](above i) -> below i -> above j.
          next[j] = (next[j] + cur[i] * dp[p][i][j]) % MOD;
        }
      }
      cur = next;
    }
    long result = 0;
    if ((last & 1) == 0) {
      for (int i = 0; i < interactNum; ++i) {
        if (interact.get(i)[0] == maxState) {
          result = cur[i];
        }
      }
    } else {
      for (int i = 0; i < interactNum; ++i) {
        result = (result + cur[i]) % MOD;
      }
    }
    return (int)result;
  }

  void permuteInteract(int pos, int aboveState, int belowState, int M, ArrayList<int[]> interact) {
    if (pos == M) {
      interact.add(new int[]{aboveState, belowState});
      return;
    }
    // don't use 2 * 2 between above and below.
    permuteInteract(pos + 1, aboveState | (1 << pos), belowState, M, interact);
    // use 2 * 2 between above and below.
    if (pos < M - 1) {
      permuteInteract(pos + 2, aboveState, belowState | (3 << pos), M, interact);
    }
  }
}
