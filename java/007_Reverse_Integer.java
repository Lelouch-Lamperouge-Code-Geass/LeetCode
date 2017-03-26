public class Solution {
    public int reverse(int x) {
        int sign = x > 0 ? 1 : -1;
        x = Math.abs(x);
        long reval = 0;
        while (x != 0) {
            reval = reval * 10 + x % 10;
            x /= 10;
        }
        reval *= sign;
        return reval > Integer.MAX_VALUE || reval < Integer.MIN_VALUE ? 0 : (int)reval;
    }
}
