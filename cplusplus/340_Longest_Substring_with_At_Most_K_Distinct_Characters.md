Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = “eceba” and k = 2,

T is "ece" which its length is 3.
  
# Solution

### Solution by other  
  
```cpp
int lengthOfLongestSubstringKDistinct(string s, int k) {
  int ctr[256] = {}, j = -1, distinct = 0, maxlen = 0;
  for (int i=0; i<s.size(); ++i) {
    distinct += ctr[s[i]]++ == 0;
    while (distinct > k)
      distinct -= --ctr[s[++j]] == 0;
    maxlen = max(maxlen, i - j);
  }
  return maxlen;
}
```

### Solution by myself

```cpp
int lengthOfLongestSubstringKDistinct(string s, int k) {
  if (s.empty() || k <= 0) return 0;
  std::vector<int> counter(256, 0);
  std::size_t start(0), max_len(0);
  int distinct(0);
  for (std::size_t i = 0, n = s.size(); i < n; ++i) {
    if (counter[s[i]] == 0) ++ distinct;
    ++ counter[s[i]];
    while (distinct > k) {
      --counter[s[start]];
      if (counter[s[start]] == 0) -- distinct;
      ++ start;
    }
    max_len = std::max(max_len, i - start + 1);
  }

  return max_len;
}

void UnitTest() {
  assert(lengthOfLongestSubstringKDistinct("eceba", 2) == 3);
  assert(lengthOfLongestSubstringKDistinct("abcdbcfde", 3) == 5);
  assert(lengthOfLongestSubstringKDistinct("abcde", 2) == 2);
  assert(lengthOfLongestSubstringKDistinct("", 10) == 0);
  assert(lengthOfLongestSubstringKDistinct("aaaaa", -1) == 0);
}
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
