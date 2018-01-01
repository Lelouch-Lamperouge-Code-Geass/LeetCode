Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Examples: 

```
"123", 6 -> ["1+2+3", "1*2*3"] 
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []
```

# Solution

My first intuitive solution is to use divide and conquer. What I though is that we can just use a function which look like ``` vector<pair<string, int>> getItems(const string & str)```, this function will return a vector of expression string and their corresponding value. However, it is not easy to implement when the operators have different priorities. For example, you get one item <"1+2 * 3", 7> and another item<"4-5", -1>, how can to concatenate theses two strings with operator '\*' ? This means divide-and-conquer is not a good option for this problem.  


This problem has a lot of edge cases to be considered:

* overflow: we use a long type once it is larger than Integer.MAX_VALUE or minimum, we get over it.
* 0 sequence: because we can't have numbers with multiple digits started with zero, we have to deal with it too.
* a little trick is that we should save the value that is to be multiplied in the next recursion.

The tricky part of this problem is that we need to treat "2\*4\*8" as a whole.

```cpp
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> reval;
        string temp("");
        addOperatorWithDFS(reval, temp , num, target, 0, 0, 0);
        return reval;
    }
private:
    void addOperatorWithDFS(vector<string> &reval,
                            const string &temp,
                            const string &num,
                            const int target,
                            const std::size_t pos,
                            const long pre_num,
                            const long cur_val
                            ) {
        if (pos == num.size()) {
            if (cur_val == target) {
                reval.emplace_back(temp);
            }
        } else {
            for (std::size_t len = 1, n = num.size(); pos + len <= n; ++ len) {
                if (len > 1 && num[pos] == '0') break; // prevent "0x"
                const string &str = num.substr(pos, len);
                const long val = std::stol(str);
                
                if (temp.empty()) {
                    addOperatorWithDFS(reval, str, num, target, pos + len, val,  val);
                } else {
                    // add '*'
                    addOperatorWithDFS(reval, temp + '*' + str, num, target, pos + len, pre_num * val, cur_val - pre_num + pre_num * val);
                    // add '+'
                    addOperatorWithDFS(reval, temp + '+' + str, num, target, pos + len, val, cur_val + val);
                    // add '-'
                    addOperatorWithDFS(reval, temp + '-' + str, num, target, pos + len, -val, cur_val - val);
                }
            }
        }
    }
};

```
