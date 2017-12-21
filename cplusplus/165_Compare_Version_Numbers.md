Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:

```
0.1 < 1.1 < 1.2 < 13.37
```

# Solution

```cpp
class Solution {
public:
    int compareVersion(string version1, string version2) {
        const std::size_t n1(version1.size()), n2(version2.size());
        std::size_t i(0), j(0);
        
        while (i < n1 || j < n2) {
            int val1(0), val2(0);
            
            // Get number between '.'
            while (i < n1 && version1[i] != '.') {
                val1 = val1 * 10 + (version1[i] - '0');
                ++ i;
            } 
            
            while (j < n2 && version2[j] != '.') {
                val2 = val2 * 10 + (version2[j] - '0');
                ++ j;
            } 
            
            if (val1 != val2) {
                return val1 > val2 ? 1 : -1;
            }
            
            // skip '.'
            ++ i, ++ j;
        }
        
        return 0;
    }
};
```
