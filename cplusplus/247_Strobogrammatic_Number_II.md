A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).  

Find all strobogrammatic numbers that are of length = n.  

For example, Given n = 2, return ["11","69","88","96"].  

# Solution

We are going to build a string of n length, what if we already know the n – 2 length solution to the problem? Then we just surround that by ‘1’ and ‘1’, ‘8’ and ‘8’, ‘6’ and ‘9’ etc.

Note that in between we can add ‘0’ and ‘0’ but at the last chance, we don’t want to surround with ‘0’ and ‘0’. Because we don’t want a “0110” in the solution. This is not part of the description of the problem. But based on the example given above, it doesn’t contain “00” in the answer, so that’s how we can guess we should not contain ‘0’ and ‘0’.


```cpp
class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        return helper(n , n);
    }
    vector<string> helper(int m, int n){
        if(m == 0) return vector<string>({""});
        if(m == 1) return vector<string>({"0", "1", "8"});
        vector<string> tmp = helper(m - 2, n), res;
        for(int i = 0; i < tmp.size(); i++){
            if(m != n) res.push_back("0" + tmp[i] + "0"); //  "0" cannot be add to the leftmost and rightmost position.
            res.push_back("1" + tmp[i] + "1");
            res.push_back("6" + tmp[i] + "9");
            res.push_back("8" + tmp[i] + "8");
            res.push_back("9" + tmp[i] + "6");
        }
        return res;
    }
};
```

```java
// iterative version ^^

public class Solution {
    public List<String> findStrobogrammatic(int n) {
        List<String> cur, ans;
        ans = new ArrayList<String>((n & 1) == 0 ? Arrays.asList("") : Arrays.asList("0", "1", "8"));
        if (n < 2) return ans;
        
        for (;n > 1; n -= 2) {
            cur = ans;
            ans = new ArrayList<String>();
            for (String i : cur) {
                if (n > 3) ans.add('0' + i + '0');
                ans.add('1' + i + '1');
                ans.add('8' + i + '8');
                ans.add('6' + i + '9');
                ans.add('9' + i + '6');
            }
        }
        
        return ans;
    }
}
```
