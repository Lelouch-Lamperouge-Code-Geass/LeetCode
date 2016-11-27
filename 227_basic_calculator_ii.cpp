
class Solution {
public:
    int calculate(string s) {
        vector<int> values;
        int cur_val(0);
        char sign('+');
        s.push_back('+'); //sentinel char
        for (const char c : s) {
            if(c ==' ') {
                continue;
            } else if (std::isdigit(c)) {
                cur_val = cur_val * 10 + (c-'0');
            } else {
                if (sign=='*') {
                    values.back() *= cur_val;
                } else if (sign=='/') {
                    values.back() /= cur_val;
                } else if (sign=='+') {
                    values.push_back(cur_val);
                } else if (sign=='-') {
                    values.push_back(-cur_val);
                } else {} // do nothing or can throw exception here
                cur_val = 0; // reset
                sign = c; // record current char
            }
        }
        return std::accumulate(values.begin(),values.end(),0);
    }
};
