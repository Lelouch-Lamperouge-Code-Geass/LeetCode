public class Solution {
    public boolean isPalindrome(int x) {
        if (x < 0 || x > 0 && x % 10 == 0) return false;
        
        int mirror = 0;
        
        while (x / 10 > mirror) {
            mirror = mirror * 10 + x % 10;
            x /= 10;
        }
        
        return x == mirror || x / 10 == mirror;
    }
}
