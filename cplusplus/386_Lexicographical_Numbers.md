Given an integer n, return 1 - n in lexicographical order.

For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

Please optimize your algorithm to use less time and space. The input size may be as large as 5,000,000.

# Solution

### Solution 1, DFS

The idea is pretty simple. If we look at the order we can find out we just keep adding digit from 0 to 9 to every digit and make it a tree.
Then we visit every node in pre-order. 

```
       1        2        3    ...
      /\        /\       /\
   10 ...19  20...29  30...39   ....
   /
  100 ... 
```
   

```cpp
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> reval;
        for (int i = 1; i <= 9; ++i) {
            dfs(reval, i, n);
        }
        return reval;
    }
private:
    void dfs(vector<int> &reval, int num, const int n) {
        if (num > n) {
            return;
        } else {
            reval.emplace_back(num);
            for (int i = 0; i <= 9 ; ++i) {
                if (num * 10 + i > n ) return;
                dfs(reval, num * 10 + i, n);
            }
        }
    }
};
```


### Solution 2

The basic idea is to find the next number to add.
Take 45 for example: if the current number is 45, the next one will be 450 (450 == 45 * 10)(if 450 <= n), or 46 (46 == 45 + 1) (if 46 <= n) or 5 (5 == 45 / 10 + 1)(5 is less than 45 so it is for sure less than n).
We should also consider n = 600, and the current number = 499, the next number is 5 because there are all "9"s after "4" in "499" so we should divide 499 by 10 until the last digit is not "9".
It is like a tree, and we are easy to get a sibling, a left most child and the parent of any node.

The methology is quite similar to solution 1.

```cpp
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> reval;
        int curr(1);
        for (int i = 1; i <= n; ++i) {
            reval.emplace_back(curr);
            if (curr * 10 <= n) {
                curr *= 10;
            } else if ( curr % 10 != 9 && curr + 1 <= n) {
                ++ curr;
            } else {
                if (curr % 10 != 9) {
                    // 192 => 2
                    curr /= 10;
                    while ( curr % 10 == 9) {
                        curr /= 10;
                    }
                    ++ curr;
                } else {
                    // 4999 => 5
                    while ( curr % 10 == 9) {
                        curr /= 10;
                    }
                    ++ curr;
                }
            }
        }
        return reval;
    }
};
```

