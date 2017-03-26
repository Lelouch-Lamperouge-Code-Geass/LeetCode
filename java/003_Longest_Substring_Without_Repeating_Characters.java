public class Solution {
    public int lengthOfLongestSubstring(String s) {
        int reval = 0, start = 0;
        HashMap<Character, Integer> hm = new HashMap<Character, Integer>();
        for (int i = 0; i < s.length(); ++i) {
            if (hm.containsKey(s.charAt(i))) {
                start = Math.max(start, hm.get(s.charAt(i)) + 1);
            }
            reval = Math.max(reval, i - start + 1);
            hm.put(s.charAt(i), i);
        }
        return reval;
    }
}
