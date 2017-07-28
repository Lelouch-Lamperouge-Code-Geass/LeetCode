A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).  

Find all strobogrammatic numbers that are of length = n.  

For example, Given n = 2, return ["11","69","88","96"].  

# Solution

This is a expansion of the version I problem. This problem has a obvious hint of divide and conquer. It can be reduced to sub problems.

We are going to build a string of n length, what if we already know the n – 2 length solution to the problem? Then we just surround that by ‘1’ and ‘1’, ‘8’ and ‘8’, ‘6’ and ‘9’ etc.

Note that in between we can add ‘0’ and ‘0’ but at the last chance, we don’t want to surround with ‘0’ and ‘0’. Because we don’t want a “0110” in the solution. This is not part of the description of the problem. But based on the example given above, it doesn’t contain “00” in the answer, so that’s how we can guess we should not contain ‘0’ and ‘0’.


```java
// recursive version
public List<String> findStrobogrammatic(int n) {
    return helper(n, n);
}

List<String> helper(int n, int m) {
    if (n == 0) return new ArrayList<String>(Arrays.asList(""));
    if (n == 1) return new ArrayList<String>(Arrays.asList("0", "1", "8"));
    
    List<String> list = helper(n - 2, m);
    
    List<String> res = new ArrayList<String>();
    
    for (int i = 0; i < list.size(); i++) {
        String s = list.get(i);
        
        if (n != m) res.add("0" + s + "0");
        
        res.add("1" + s + "1");
        res.add("6" + s + "9");
        res.add("8" + s + "8");
        res.add("9" + s + "6");
    }
    
    return res;
}
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
