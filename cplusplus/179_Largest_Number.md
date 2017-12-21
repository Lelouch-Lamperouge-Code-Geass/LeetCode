Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.

# Solution
  
```cpp
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        std::vector<std::string> strs;
        for (int num : nums) {
            strs.emplace_back(std::to_string(num));
        }
        
        std::sort(strs.begin(), strs.end(), [](const string &left, const string &right){
            return left + right > right + left;
        });
        
        std::string reval = std::accumulate(strs.begin(), strs.end(), std::string(""));
        
        if (reval.size() > 1 && reval[0] == '0') {
            return "0";
        } else {
            return reval;
        }
    }
};
```  
  
A different style with functor.  
  
```cpp
class Solution {
public:
  string largestNumber(vector<int>& nums) {
    vector<string> vec;
    for (int num : nums) {
      vec.push_back( std::to_string(num) );
    }
    std::sort(vec.begin(),vec.end(), Compare());
    string reval = std::accumulate(vec.begin(),vec.end(),string(""));
    return reval.size() > 1 && reval[0]=='0' ? "0" : reval;
  }
private:
  class Compare {
  public:
    bool operator() (const string & left, const string & right) {
      return left + right > right + left;
    }
  };
};
```

