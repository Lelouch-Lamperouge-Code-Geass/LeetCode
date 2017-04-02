public class Solution {
    private int[] getKmpVec(String str) {
        if (str == null || str.isEmpty()) return null;
        final int str_length = str.length();
        int[] reval = new int[str_length];
        
        int len = 0, pos = 1;
        while (pos < str_length) {
            if (str.charAt(pos) == str.charAt(len)) {
                reval[pos] = len + 1;
                ++ pos;
                ++ len;
            } else {
                if (len > 0) {
                    len = reval[len - 1];
                } else {
                    reval[pos] = 0;
                    ++ pos;
                }
            }
        }
        
        return reval;
    }
    
    public int strStr(String haystack, String needle) {
        if (haystack == null) return -1;
        if (needle == null || needle.isEmpty()) return 0;
        int[] kmp = getKmpVec(needle);
        int i = 0, j = 0;
        while (i < haystack.length()) {
            if (haystack.charAt(i) == needle.charAt(j)) {
                ++ i; 
                ++ j;
                if (j == needle.length()) return i - j;
            } else {
                if (j == 0) {
                    ++ i;
                } else {
                    j = kmp[j - 1];
                }                
            }
        }
        
        return -1;
    }
}
