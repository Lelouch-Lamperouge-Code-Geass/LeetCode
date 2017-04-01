public class Solution {
    private Character getLeftParenthese(Character c) {
        if (c == ')') return '(';
        if (c == ']') return '[';
        if (c == '}') return '{';
        return '#';
    }
    public boolean isValid(String s) {
        Stack<Character> my_stack = new Stack<Character>();
        for (char c : s.toCharArray()) {
            if (c == '(' || c == '[' || c == '{') {
                my_stack.push(c);
            } else if (c == ')' || c == ']' || c == '}') {
                if (my_stack.empty() || my_stack.peek() != getLeftParenthese(c) ) {
                    return false;
                } else {
                    my_stack.pop();
                }
            } else {
                continue;
            }
        }
        return my_stack.empty();
    }
}
