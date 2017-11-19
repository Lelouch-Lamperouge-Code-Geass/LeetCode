Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:  

```
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
```

# Solution

This problem is asking for "all possible valid" ip address based on input string. So it is asking for all solutions to a problem, and these solutions need to be checked in order to meet some requirements. What does this tell you? Right, this is a backtracking problem.

> Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons each partial candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

__Anothing thing is that you need to check with interviewer whether this ip address is IPv4 or IPv6.__ Because the IPv4 address is made up of 32 bits (4 bytes) and the IPv6 address is 128 bits (16 bytes).

Below discussion will based on IPv4.

Some corner cases :

1. The ip address should have 4 parts.
2. Each part of IP address should not be "00", "01", etc. Leaning 0 are not allowed.
3. Each part should not be more than 255.

```cpp
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> reval;
        checkWithBacktracking(reval, "", 0, s, 0);
        return reval;
    }
private:
    void checkWithBacktracking(vector<string> &reval, 
                               string temp,
                               int part_count,
                               const string &s,
                               const std::size_t pos) {
        if (pos == s.size()) {
            if (!temp.empty() && part_count == 4) {
                reval.emplace_back(temp);
            }
        } else {
            if (byte_count == 4) return; // can't be more than 4 bytes
            for (std::size_t len = 1; len <= 3 && pos + len <= s.size(); ++len) {
                if (len > 1 && s[pos] == '0') break; // can't be "00", "01"
                
                string seg_str(s.substr(pos, len));
                int val = std::stoi(seg_str);
                
                if (val > 255) break; // Must <= 255
                
                string next_temp = temp.empty() ? seg_str : temp + '.' + seg_str;
                checkWithBacktracking(reval, next_temp, part_count + 1, s, pos + len);
            }
        }
    }
};
```

A different solution.

```cpp
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        for (int a=1;a<=3;++a) 
        for (int b=1;b<=3;++b)  
        for (int c=1;c<=3;++c)  
        for (int d=1;d<=3;++d){
            if ( a+b+c+d == s.size() ) {
                string a_str = s.substr(0,a);
                string b_str = s.substr(a,b);
                string c_str = s.substr(a+b,c);
                string d_str = s.substr(a+b+c,d);
                int a_val = std::stoi( s.substr(0,a) );
                int b_val = std::stoi( s.substr(a,b) );      
                int c_val = std::stoi( s.substr(a+b,c) );
                int d_val = std::stoi( s.substr(a+b+c,d) );
                if(a_val>255||b_val>255||c_val>255||d_val>255) continue;
                string cur_str = std::to_string(a_val)+'.'+std::to_string(b_val)+'.'+std::to_string(c_val)+'.'+std::to_string(d_val);
                if(cur_str.size() == s.size()+3)
                    res.push_back(cur_str);
            }
        }
        return res;
    }
};
```
