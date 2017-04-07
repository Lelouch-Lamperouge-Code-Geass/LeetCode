// Solution one, O(n) time, one stack
public class Solution {
    public int longestValidParentheses(String s) {
        Stack<Integer> invalid_pos = new Stack<Integer>();
        for (int i = 0, length = s.length(); i < length; ++i) {
            if (invalid_pos.isEmpty() 
                || s.charAt(i) == '('
                || s.charAt(i) == ')' && s.charAt(invalid_pos.peek()) != '(') {
                invalid_pos.push(i);
            } else {
                invalid_pos.pop();
            }
        }
        
        int reval = 0;
        int open_end = s.length();
        while (!invalid_pos.isEmpty()) {
            int open_begin = invalid_pos.peek();
            int len = open_end - open_begin - 1;
            reval = Math.max(reval, len);
            open_end = open_begin;
            invalid_pos.pop();
        }
        // Don't forget the first valid
        reval = Math.max(reval, open_end);
        return reval;
    }
}

// Solution 2,  O(n) time, one stack
public class Solution {
    public int longestValidParentheses(String s) {
        Stack<Integer> stack = new Stack<Integer>();
        int reval = 0;
        int left = -1;
        for(int j=0;j<s.length();j++){
            if(s.charAt(j)=='(') stack.push(j);            
            else {
                if (stack.isEmpty()) left=j;
                else{
                    stack.pop();
                    if(stack.isEmpty()) reval = Math.max(reval,j-left);
                    else reval = Math.max(reval,j-stack.peek());
                }
            }
        }
        return reval;
    }
}

// Solution 3, DP, O(n) solution without using stack
public class Solution {
    public int longestValidParentheses(String s) {
        final int s_len = s.length();
        int reval = 0;
        int[] longest_end_here = new int[s_len];
        for (int i = 1; i < s_len; ++i) {
            if (s.charAt(i) == ')') {
                if (s.charAt(i-1) == '(') {
                    longest_end_here[i] = i >= 2 ?  longest_end_here[i-2] + 2 : 2;
                } else { // s.charAt(i-1) == ')'
                    int pre_len = longest_end_here[i-1];
                    if (i - pre_len >= 1 && s.charAt(i - pre_len - 1) == '(' ) {
                        longest_end_here[i] = pre_len + 2 
                        + (i - pre_len > 2 ? longest_end_here[i - pre_len - 2] : 0);
                    }
                }
            }
            reval = Math.max(reval, longest_end_here[i]);
        }
        return reval;
    }
}
