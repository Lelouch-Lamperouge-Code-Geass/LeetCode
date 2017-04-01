public class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> reval = new ArrayList<String>();
        int left_paren = n, right_paren = n;
        StringBuilder sb = new StringBuilder();
        checkWithBacktracking(reval, left_paren, right_paren, sb);
        return reval;
    }
    
    private void checkWithBacktracking(List<String> list,
                                int left_paren, 
                                int right_paren,
                                StringBuilder sb) {
        if (left_paren == 0 && right_paren == 0) {
            list.add(sb.toString());
        } else {
            // try add '('
            if (left_paren > 0) {
                sb.append('(');
                checkWithBacktracking(list, left_paren - 1, right_paren, sb);
                sb.setLength(sb.length() - 1);
            }
            
            // try add ')'
            if (left_paren < right_paren) {
                sb.append(')');
                checkWithBacktracking(list, left_paren, right_paren - 1, sb);
                sb.setLength(sb.length() - 1);
            }
        }
    }
}
