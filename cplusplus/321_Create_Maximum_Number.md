Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits. You should try to optimize your time and space complexity.

Example 1:

```
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
return [9, 8, 6, 5, 3]
```

Example 2:

```
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
return [6, 7, 6, 0, 4]
```

Example 3:

```
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
return [9, 8, 9]
```

# Solution

### Solution 1

The basic idea:

To create max number of length k from two arrays, you need to create max number of length i from array one and max number of length k-i from array two, then combine them together. After trying all possible i, you will get the max number created from two arrays.

Therefore, we need to solve two simpler sub-problems:

1. Create the maximum number of one array with specified subarray length.  
2. Create the maximum number of by merging two arrays.  

Optimization:

1. Suppose nums1 = [3, 4, 6, 5], nums2 = [9, 1, 2, 5, 8, 3], the maximum number you can create from nums1 is [6, 5] with length 2. For nums2, it's [9, 8, 3] with length 3. Merging the two sequence, we have [9, 8, 6, 5, 3], which is the max number we can create from two arrays without length constraint. If the required length k<=5, we can simply trim the result to required length from front. For instance, if k=3, then [9, 8, 6] is the result.

2. Suppose we need to create max number with length 2 from num = [4, 5, 3, 2, 1, 6, 0, 8]. The simple way is to use a stack, first we push 4 and have stack [4], then comes 5 > 4, we pop 4 and push 5, stack becomes [5], 3 < 5, we push 3, stack becomes [5, 3]. Now we have the required length 2, but we need to keep going through the array in case a larger number comes, 2 < 3, we discard it instead of pushing it because the stack already grows to required size 2. 1 < 3, we discard it. 6 > 3, we pop 3, since 6 > 5 and there are still elements left, we can continue to pop 5 and push 6, the stack becomes [6], since 0 < 6, we push 0, the stack becomes [6, 0], the stack grows to required length again. Since 8 > 0, we pop 0, although 8 > 6, we can't continue to pop 6 since there is only one number, which is 8, left, if we pop 6 and push 8, we can't get to length 2, so we push 8 directly, the stack becomes [6, 8].

3. In the basic idea, we mentioned trying all possible length i. If we create max number for different i from scratch each time, that would be a waste of time. Suppose num = [4, 9, 3, 2, 1, 8, 7, 6], we need to create max number with length from 1 to 8. For i==8, result is the original array. For i==7, we need to drop 1 number from array, since 9 > 4, we drop 4, the result is [9, 3, 2, 1, 8, 7, 6]. For i==6, we need to drop 1 more number, 3 < 9, skip, 2 < 3, skip, 1 < 2, skip, 8 > 1, we drop 1, the result is [9, 3, 2, 8, 7, 6]. For i==5, we need to drop 1 more, but this time, we needn't check from beginning, during last scan, we already know [9, 3, 2] is monotonically non-increasing, so we check 8 directly, since 8 > 2, we drop 2, the result is [9, 3, 8, 7, 6]. For i==4, we start with 8, 8 > 3, we drop 3, the result is [9, 8, 7, 6]. For i==3, we start with 8, 8 < 9, skip, 7 < 8, skip, 6 < 7, skip, by now, we've got maximum number we can create from num without length constraint. So from now on, we can drop a number from the end each time. The result is [9, 8, 7], For i==2, we drop last number 7 and have [9, 8]. For i==1, we drop last number 8 and have [9].


#### Pitfall
__The most tricky part here is when we merge two vectors together into one, how can we gaurantee that the merged vector is the max number we can get?__

For example, 
```
[6,7]
[6,0,4]
```
We have 6 when i = 0 and j=0, which 6 should we choose?
```
[9, 7, 2, 3, 4, 6]
[8, 7, 2, 3, 4, 5]
```

We have 7 when i = 1 and j = 1, which 7 should we choose?

__The key is to compare the left subarray include that number, and choose the one is [lexicographically larger](https://en.wikipedia.org/wiki/Lexicographical_order).__

```cpp
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        const size_t size_1(nums1.size()), size_2(nums2.size());
        
        vector<int> max_number;
        
        for (size_t len1 = 0; len1 <= size_1 && len1 <= k; ++len1) {
            if (k - len1 > size_2) continue;
            vector<int> candidate(maxNumberWithMerge(maxSubNumber(nums1, len1), maxSubNumber(nums2, k - len1)));
            if (isLexicographicalGreater(candidate, max_number, 0, 0)) {
                max_number = candidate;
            }
        }
        return max_number;
    }
private:
    // Return true/false whether subarray [pos1:end) of nums1 is lexicographically 
    // greater than subarray [pos2:end) of nums2
    bool isLexicographicalGreater(const vector<int>& nums1, 
                                  const vector<int>& nums2,
                                  size_t pos1,
                                  size_t pos2) {
        while (pos1 < nums1.size() && pos2 < nums2.size()
              && nums1[pos1] == nums2[pos2]) {
            ++ pos1, ++ pos2;
        }
        
        return pos2 == nums2.size() || pos1 < nums1.size() && nums1[pos1] > nums2[pos2];
    }
    
    // Return a subarray which representing the maximum number
    // we can get from nums with size len.
    vector<int> maxSubNumber(const vector<int>& nums,
                             size_t len) {
        vector<int> reval;
        size_t number_left(len);
        for (size_t i = 0, n = nums.size(); i < n; ++i) {
            while (!reval.empty() && reval.back() < nums[i] 
                   && (reval.size() - 1 + n - i) >= len // Make sure we have enough numbers to reach len
                  ) {
                reval.pop_back();
            }
            reval.emplace_back(nums[i]);
        }
        return vector<int>(reval.begin(), reval.begin() + len);
    }
    
    // Return the maximum number we can get by merging two numbers.
    vector<int> maxNumberWithMerge(const vector<int>& nums1, 
                                   const vector<int>& nums2) {
        
        const size_t size_1(nums1.size()), size_2(nums2.size()), total_size(size_1 + size_2);
        vector<int> reval(total_size, 0);
        
        for (size_t index(0), i(0), j(0); index < total_size; ++ index) {
            reval[index] = isLexicographicalGreater(nums1, nums2, i, j) ? nums1[i++] : nums2[j++];
        }
        
        return reval;
    }
};
```





