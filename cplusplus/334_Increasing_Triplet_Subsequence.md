Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

Formally the function should:

```
Return true if there exists i, j, k 
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
```

Your algorithm should run in O(n) time complexity and O(1) space complexity.

Examples:

```
Given [1, 2, 3, 4, 5],
return true.

Given [5, 4, 3, 2, 1],
return false.
```
    
# Solution

### Solution one

The basic condition is at any time, small < big.  
So for any arbitrary element later, we call it i, there are three possibilities:  
a). i <= small < big, then just update small, and it will not change our basic condition, which is small < big.  
b). small < i <= big, then just update big. small < big still exists.  
c.) small < big < i, then we find a increasing triplet subsequence.  

```
Example:   
initial : [1, 2, 0, 3], small = MAX, big = MAX
loop1 : [1, 2, 0, 3], small = 1, big = MAX
loop2 : [1, 2, 0, 3], small = 1, big = 2
loop3 : [1, 2, 0, 3], small = 0, big = 2 // <- Uh oh, 0 technically appeared after 2
loop4 : return true since 3 > small && 3 > big // Isn't this a violation??

If you observe carefully, the moment we updated big from MAX to some other value, that means that 
there clearly was a value less than it (which would have been assigned to small in the past). 
What this means is that once you find a value bigger than big, you've implicitly found an increasing triplet.
```

Before coding I also thought about this solution and I did’t think that will work, as it appears to be very naïve and greedy: find first smallest, then find second smallest, then find the third and bingo. I argued myself it cannot pass the case like [1,2,0,3] since c1 is changed.

But when I take a closer look, it does [1,2,0,3] very well. And I realize that c1 and c2 are indeed having the meaning of:

```
C1 = so far best candidate of end element of a one-cell subsequence to form a triplet subsequence

C2 = so far best candidate of end element of a two-cell subsequence to form a triplet subsequence

So c1 and c2 are the perfect summary of history.
```

__time complexity is O(n), space complexity is O(1)__

```cpp
class Solution {
public:
  bool increasingTriplet(vector<int>& nums) {
  // start with two largest values, as soon as we find a number bigger than both, 
  // while both have been updated, return true.
    int small(INT_MAX), big(INT_MAX);
    std::vector<int> sequence;
    for (int num : nums) {
      if (num <= small) { small = num; } // update small if num is smaller than both
      else if (num <= big) { big = num; } // update big only if greater than small but smaller than big
      else return true; // return if you find a number bigger than both
    }
    return false;
  }
};
```

### Solution 2 : Longest Increasing Sequence, O(nlogn)

This solution doesn't meet the requirement of time complexity and space complexity.
But it is still worth to check it out.
    
__time complexity is O(nlogn), space complexity is O(n)__

```cpp
class Solution {
public:
  bool increasingTriplet(vector<int>& nums) {
    std::vector<int> sequence;
    for (int num : nums) {
      auto iter = std::lower_bound(sequence.begin(), sequence.end(), num);
      if (iter == sequence.end()) {
        sequence.push_back(num);
      } else {
        *iter = num;
      }
      if (sequence.size() == 3) return true;
    }
    return false;
  }
};
```
