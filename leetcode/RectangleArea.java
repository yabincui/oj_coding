public class RectangleArea {
  public int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    long area = (long)(C - A) * (D - B);
    area += (long)(G - E) * (H - F);
    long lx = Math.max(A, E);
    long ly = Math.max(B, F);
    long hx = Math.min(C, G);
    long hy = Math.min(D, H);
    if (lx <= hx && ly <= hy) {
      long area1 = (long)(hx - lx) * (hy - ly);
      area -= area1;
    }
    return (int)area;
  }
}
