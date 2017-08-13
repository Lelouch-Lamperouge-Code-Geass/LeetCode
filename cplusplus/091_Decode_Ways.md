A message containing letters from A-Z is being encoded to numbers using the following mapping:

```
'A' -> 1
'B' -> 2
...
'Z' -> 26
```

Given an encoded message containing digits, determine the total number of ways to decode it.  

For example,  
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).  

The number of ways decoding "12" is 2.  

# Solution

I used a dp array of size n + 1 to save subproblem solutions. dp[0] means an empty string will have one way to decode, dp[1] means the way to decode a string of size 1. I then check one digit and two digit combination and save the results along the way. In the end, dp[n] will be the end result.

```cpp
class Solution {
public:
    int numDecodings(string s) {
        if(s.empty()||s[0]=='0')
            return 0;
        const int s_size = s.size();
        vector<int> dp(s_size,0);
        dp[0]=1;
        for(int i=1; i<s.size(); i++) {
            int v = (s[i-1]-'0')*10 + (s[i]-'0');
            // + dp[i-2] ?
            if( v<=26 && v>=10) dp[i] =  (i>=2? dp[i-2]:1);
            // + dp[i-1] ?
            if(s[i]!='0') dp[i] += dp[i-1];
            if(dp[i]==0)return 0;
        }
        return dp[s_size-1];
    }

};
```
