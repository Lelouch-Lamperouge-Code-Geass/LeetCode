Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

```
Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
```

Example 2:

```
Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
```

# Solution

# Solution 1, divide and conquer

In computer science, divide and conquer (D&C) is an algorithm design paradigm based on multi-branched recursion. A divide and conquer algorithm works by recursively breaking down a problem into two or more sub-problems of the same or related type, until these become simple enough to be solved directly. The solutions to the sub-problems are then combined to give a solution to the original problem.

Understanding and designing D&C algorithms is a complex skill that requires a good understanding of the nature of the underlying problem to be solved. As when proving a theorem by induction, it is often necessary to replace the original problem with a more general or complicated problem in order to initialize the recursion, and there is no systematic method for finding the proper generalization. These D&C complications are seen when optimizing the calculation of a Fibonacci number with efficient double recursion.

The correctness of a divide and conquer algorithm is usually proved by mathematical induction, and its computational cost is often determined by solving recurrence relations.

```cpp
class Solution {
public:
    int longestSubstring(string s, int k) {
        return helper(s, 0, s.size(), k);
    }
private:
    int helper(const string & s, std::size_t begin, std::size_t end, const int k) {
        vector<int> counter(26, 0);  // we know it is lowercase only
        
        for (std::size_t i = begin; i < end; ++i) {
            ++ counter[s[i] - 'a'];
        }
        
        for (std::size_t i = begin; i < end; ++i) {
            if (counter[s[i] - 'a'] < k) {
                int left_max_len = helper(s, begin, i, k);
                int right_max_len = helper(s, i + 1, end, k);
                return std::max(left_max_len, right_max_len);
            }
        }
        
        // No violate char
        
        return end - begin;
        
    }
};
```
