public class Solution {
    public int myAtoi(String str) {
        int index = 0;
        int str_length = str.length();

        //  Remove Spaces
        while (index < str_length && str.charAt(index) == ' ') ++ index;

        if (index == str_length) return 0;

        // Handle signs
        int sign = 1;
        if (str.charAt(index) == '-' || str.charAt(index) == '+') {
            sign = str.charAt( index ) == '-' ? -1 : 1;
            ++ index;
        }

        // Convert number and avoid overflow
        long val = 0;
        while (index < str_length && Character.isDigit(str.charAt(index)) ) {
            val = val * 10 + (str.charAt(index) - '0');
            if (val > Integer.MAX_VALUE )
                return sign == 1 ? Integer.MAX_VALUE : Integer.MIN_VALUE;
            ++ index;
        }

        val *= sign;

        return (int)val;
    }
}
