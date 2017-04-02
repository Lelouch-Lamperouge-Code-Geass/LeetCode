public class Solution {
    public int divide(int dividend, int divisor) {
        if (divisor == 0) return Integer.MAX_VALUE;
        if (dividend == 0) return 0;
        
        int sign =  1 ;
        if ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0))
            sign  = -1;
        
        long abs_dividend = Math.abs((long)dividend); // overflow can happen here, e.g. -2147483648
        long abs_divisor = Math.abs((long)divisor);
        
        long reval = 0;
        while (abs_dividend >= abs_divisor) {
            long sum = abs_divisor, count = 1;
            
            while ( (sum << 1) <= abs_dividend) {
                sum <<= 1;
                count <<= 1;
            }
            
            abs_dividend -= sum;
            reval += count;
            
        }
        
        reval *= sign;
        if (reval > Integer.MAX_VALUE || reval < Integer.MIN_VALUE) return Integer.MAX_VALUE;
        return (int) reval;
    }
}
