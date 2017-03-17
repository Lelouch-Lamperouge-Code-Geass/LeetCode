class Solution {
public:
/*
Only 5 possible input we need to pay attention:

digit: it should be one digit from the current number
'+': number is over, we can add the previous number and start a new number
'-': same as above
'(': push the previous result and the sign into the stack, set result to 0, just calculate the new result within the parenthesis.
')': pop out the top two numbers from stack, first one is the sign before this pair of parenthesis, second is the temporary result before this pair of parenthesis. We add them together.

*/
    int calculate(string s) {
        stack<int> my_stack;// res,sign,res,sign
        int sign(1),res(0), N(s.size());
        for (int i=0;i<N;++i) {
            if ( std::isdigit(s[i]) ) {
                int cur_num = s[i] - '0';
                while ( i+1 < N && std::isdigit(s[i+1]) ) {
                    cur_num = cur_num * 10 + s[i+1] - '0';
                    ++ i;
                }
                res += cur_num * sign;
            } else if ( s[i] == '+' ) {
                sign = 1; // sign of next number
            } else if ( s[i] == '-' ) {
                sign = -1; // sign of next number
            } else if ( s[i] == '(' ) {
                my_stack.push(res); // push previous result
                my_stack.push(sign);// push the sign before (
                res = 0; //reset result, it will be used to calculate the sum within ()
                sign = 1;
            } else if ( s[i] == ')' ) {
                // res right now is the sum within current parenthesis
                res *= my_stack.top(), my_stack.pop(); // multiply sign before ( 
                res += my_stack.top(), my_stack.pop(); // add with previous res 
            }
        }
        return res;
    }
};
