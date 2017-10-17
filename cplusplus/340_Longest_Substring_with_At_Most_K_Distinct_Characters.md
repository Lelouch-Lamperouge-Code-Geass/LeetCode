Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = “eceba” and k = 2,

T is "ece" which its length is 3.
  
# Solution

__Time complexity O(n), space complexity O(1).__

```cpp
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
          int distinct_count(0);
          std::vector<std::size_t> counter(256, 0);
          std::size_t start(0), max_len(0);
          for (std::size_t i = 0, n = s.size(); i < n; ++i) {
            if (counter[s[i]]++ == 0) {
              ++ distinct_count;
            }

            while (distinct_count > k) {
              if (--counter[s[start]] == 0) {
                -- distinct_count;
              }
              ++ start;
            }

            max_len = std::max(max_len, i - start + 1);
          }

          return max_len;
    }
};
```

# Follow-up

* https://discuss.leetcode.com/topic/48827/java-o-nlogk-using-treemap-to-keep-last-occurrence-interview-follow-up-question/7

Solving the problem with O(n) time is not enough, some interviewer may require this solution as a followup. Instead of recording each char's count, we keep track of char's last occurrence. If you consider k as constant, it is also a O(n) algorithm.

inWindow keeps track of each char in window and its last occurrence position

lastOccurrence is used to find the char in window with left most last occurrence. A better idea is to use a PriorityQueue, as it takes O(1) to getMin, However Java's PQ does not support O(logn) update a internal node, it takes O(n). TreeMap takes O(logn) to do both getMin and update.
Every time when the window is full of k distinct chars, we lookup TreeMap to find the one with leftmost last occurrence and set left bound j to be 1 + first to exclude the char to allow new char coming into window.
  
```java
 public int lengthOfLongestSubstringKDistinct(String str, int k) {
        if (str == null || str.isEmpty() || k == 0) return 0;
        TreeMap<Integer, Character> lastOccurrence = new TreeMap<>();
        Map<Character, Integer> inWindow = new HashMap<>();
        int j = 0, max = 1;
        for (int i = 0; i < str.length(); i++) {
            char in = str.charAt(i);
            //update or add in's position in both maps
            if (inWindow.containsKey(in)) {
                lastOccurrence.remove(inWindow.get(in));
            }
            inWindow.put(in, i);
            lastOccurrence.put(i, in);
            // make sure the size satisfies the requirement
            if (inWindow.size() > k) { 
                int first = lastOccurrence.firstKey();
                char out = lastOccurrence.get(first);
                inWindow.remove(out);
                lastOccurrence.remove(first);
                j = first + 1;
            }
            max = Math.max(max, i - j + 1);
        }
        return max;
    }
```    

# Follow-up

* 395_Longest_Substring_with_At_Least_K_Repeating_Characters
