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

This problem has a lot of edge cases to be considered:

* overflow: we use a long type once it is larger than Integer.MAX_VALUE or minimum, we get over it.
* 0 sequence: because we can't have numbers with multiple digits started with zero, we have to deal with it too.
* a little trick is that we should save the value that is to be multiplied in the next recursion.

> My first intuitive solution is to use divide and conquer. We just need a function which look like ``` vector<pair<string, int>> getItems(const string & str)```, this function will return a vector of expression string and their corresponding value. However, it is not easy to implement when the operators have different priorities. For example, you get one item <"1+2 * 3", 7> and another item<"4-5", -1>, how can to concatenate theses two strings with operator '*' ? 


```cpp
class Solution {
public:
  vector<string> addOperators(string num, int target) {
    vector<string> result;
    if(num.empty()) return result;
    string temp("");
    backtracking(result,temp,num,0,target,0,0);
    return result;
  }
private:
  void backtracking(vector<string> & result,
                    const string & temp,
                    const string & num,
                    const int start,
                    const int target,
                    const long val,
                    const long pre){
    if(start==num.size() ){
      if(val == target) result.push_back(temp);
    } else {
      const int num_size(num.size());
      for (int i=start;i<num_size;++i) {
        if (num[start]=='0' && i>start) break; // taking care of "03"
        const string & x_str = num.substr(start,i-start+1);
        long x = std::stol(x_str);
        if (start==0) { // first number
          backtracking(result,x_str,num,i+1,target,x,x);
        } else {
          backtracking(result,temp+"+"+x_str,num,i+1,target,val+x,x);
          backtracking(result,temp+"-"+x_str,num,i+1,target,val-x,-x);
          backtracking(result,temp+"*"+x_str,num,i+1,target,val-pre+pre*x,pre*x);
        }
      }
    }
  }
};

```
