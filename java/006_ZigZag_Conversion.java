public class Solution {
    public String convert(String s, int numRows) {
        if(numRows <= 1) return s;
        StringBuilder[] sb = new StringBuilder[numRows];
        for (int i = 0; i < numRows; ++i) sb[i] = new StringBuilder("");
        int row = 0, step = 1;
        for (int i = 0; i < s.length(); ++i) {
            sb[row].append(s.charAt(i));
            if (row == 0) step = 1;
            if (row == numRows - 1) step = -1;
            row += step;
        }

        for (int i = 1; i < numRows; ++i) {
            sb[0].append(sb[i].toString());
        }

        return sb[0].toString();
    }
}
