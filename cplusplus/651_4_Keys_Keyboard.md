Imagine you have a special keyboard with the following keys:

```
Key 1: (A): Print one 'A' on screen.

Key 2: (Ctrl-A): Select the whole screen.

Key 3: (Ctrl-C): Copy selection to buffer.

Key 4: (Ctrl-V): Print buffer on screen appending it after what has already been printed.
```

Now, you can only press the keyboard for N times (with the above four keys), find out the maximum numbers of 'A' you can print on screen.

#### Example 1:

```
Input: N = 3
Output: 3
Explanation: 
We can at most get 3 A's on screen by pressing following key sequence:
A, A, A
```

#### Example 2:

```
Input: N = 7
Output: 9
Explanation: 
We can at most get 9 A's on screen by pressing following key sequence:
A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
```

#### Note:

* 1 <= N <= 50
* Answers will be in the range of 32-bit signed integer.

# Solution

We use i steps to reach maxA(i) then use the remaining n - i steps to reach n - i - 1 copies of maxA(i)

For example:

```
A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
Here we have n = 7 and we used i = 3 steps to reach AAA
Then we use the remaining n - i = 4 steps: Ctrl A, Ctrl C, Ctrl V, Ctrl V, to reach n - i - 1 = 3 copies of AAA
```

We either don't make copies at all, in which case the answer is just n, or if we want to make copies, we need to have 3 steps reserved for Ctrl A, Ctrl C, Ctrl V so i can be at most n - 3

```cpp
class Solution {
public:
    int maxA(int N) {
        static std::vector<int> dp = {0, 1, 2, 3, 4};
        
        while (N + 1 > dp.size()) {
            int j = dp.size();
            int cur_max = j;
            for (int i = 1; i + 3 <= j; ++i) {
                cur_max = std::max(cur_max, dp[i] * (j - i - 1));
            }
            dp.emplace_back(cur_max);
        }
        
        return dp[N];
    }
};
```
