public class ReverseBits {
  public int reverseBits(int n) {
    int[] bits = new int[32];
    for (int i = 0; i < 32; ++i) {
      bits[i] = (n >> i) & 1;
    }
    int result = 0;
    for (int i = 0; i < 32; ++i) {
      result |= (bits[i] << (31 - i));
    }
    return result;
  }
}
