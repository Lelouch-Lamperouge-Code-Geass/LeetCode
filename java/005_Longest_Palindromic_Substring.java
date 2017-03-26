// The most intuitive solution is check any index pair of the string
// whether it can generate a longer palindrom or not. Time compexity
// is O(N^2).

public class Solution {
    public String longestPalindrome(String s) {
        if (s != null && s.isEmpty()) return s;
        int start = 0, max_len = 1;
        for (int i = 1; i < s.length(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (i - j + 1 > max_len  && isPalindrom(s, j, i) ) {
                    start = j;
                    max_len = i - j + 1;
                }
            }
        }
        return s.substring(start, start + max_len);
    }

    private boolean isPalindrom(String s, int start, int end) {
        while (start < end) {
            if (s.charAt(start) != s.charAt(end)) {
                return false;
            } else {
                ++ start;
                -- end;
            }
        }
        return true;
    }
}

// Solution two
public class Solution {
    public String longestPalindrome(String s) {
        if (s == null || s.isEmpty()) return s;
        int start = 0, max_len = 1;
        for (int i = 0; i < s.length(); ) {
            int left = i, right = i;

            // skip duplicates as far as possible
            while (right + 1 < s.length() && s.charAt(i) == s.charAt(right + 1)) ++ right;
            i = right + 1;

            // expand
            while (left >= 1 && right + 1 < s.length()
                   && s.charAt(left-1) == s.charAt(right+1)) {
                -- left;
                ++ right;
            }

            int length = right - left + 1;
            if (length > max_len) {
                start = left;
                max_len = length;
            }

        }
        return s.substring(start, start + max_len);
    }
}
