Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

```
For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.
```

##### Note:

You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

# Solution

### Solution one

```cpp
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        std::size_t pos1(-1), pos2(-1);
        
        std::size_t min_distance(words.size());
        for (std::size_t i = 0, n = words.size(); i < n; ++i) {
            if (words[i] == word1) {
                pos1 = i;
            }
            
            if (words[i] == word2) {
                pos2 = i;
            }
            
            if (pos1 != -1 && pos2 != -1) {
                min_distance = std::min(min_distance, pos1 < pos2 ? pos2 - pos1 : pos1 - pos2);
            }
        }
        
        return min_distance;
    }
};
```


### Solution two, sliding window

For sliding window problem, the most tricky part is when can we begin to increase start position of the sliding window.

We know that sliding window has a "valid criteria", which is a criteria that makes the window "valid" so that we can compare the window length with the min_len.

Once the criteria is valid, we begin to increase the start position of the window, and compare the valid window length with min_len until the start position make the "valid criteria" not valid any more. If you think about it, this "increasing start position" process is actually check the valid window length whose "end" position is i.

Therefore, you can see that sliding window problem is within the scope of dynamic programming paradigm.

If we use a vector min_len_end_with to record the minimal valid window length ends with position i , then:

1. If no valid window on i, min_len_end_with[i] = SizeOfInputVector or -1 whatever makes you happy.  
2. If there is valid window on i, min_len_end_with[i] records the minimal length of window ends with i.  

Our final result will be the Min {for each i : min_len_end_with[i]}.

The below solution is simply a O(1) optimized solution.

```cpp
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        std::size_t word1_count(0), word2_count(0);
        
        std::size_t start(0), min_len(words.size());
        for (std::size_t i = 0, n = words.size(); i < n; ++i) {
            if (words[i] == word1) {
                ++ word1_count;
            }
            
            if (words[i] == word2) {
                ++ word2_count;
            }
            
            while (word1_count > 0 && word2_count > 0) {
                min_len = std::min(min_len, i + 1 - start);
                if (words[start] == word1) {
                    -- word1_count;
                }
                
                if (words[start] == word2) {
                    -- word2_count;
                }
                
                ++ start;
            }
        }
        
        return min_len - 1;
    }
};
```
