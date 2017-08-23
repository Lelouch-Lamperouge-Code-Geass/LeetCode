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

The basic idea:

To create max number of length k from two arrays, you need to create max number of length i from array one and max number of length k-i from array two, then combine them together. After trying all possible i, you will get the max number created from two arrays.

Optimization:

1. Suppose nums1 = [3, 4, 6, 5], nums2 = [9, 1, 2, 5, 8, 3], the maximum number you can create from nums1 is [6, 5] with length 2. For nums2, it's [9, 8, 3] with length 3. Merging the two sequence, we have [9, 8, 6, 5, 3], which is the max number we can create from two arrays without length constraint. If the required length k<=5, we can simply trim the result to required length from front. For instance, if k=3, then [9, 8, 6] is the result.

2. Suppose we need to create max number with length 2 from num = [4, 5, 3, 2, 1, 6, 0, 8]. The simple way is to use a stack, first we push 4 and have stack [4], then comes 5 > 4, we pop 4 and push 5, stack becomes [5], 3 < 5, we push 3, stack becomes [5, 3]. Now we have the required length 2, but we need to keep going through the array in case a larger number comes, 2 < 3, we discard it instead of pushing it because the stack already grows to required size 2. 1 < 3, we discard it. 6 > 3, we pop 3, since 6 > 5 and there are still elements left, we can continue to pop 5 and push 6, the stack becomes [6], since 0 < 6, we push 0, the stack becomes [6, 0], the stack grows to required length again. Since 8 > 0, we pop 0, although 8 > 6, we can't continue to pop 6 since there is only one number, which is 8, left, if we pop 6 and push 8, we can't get to length 2, so we push 8 directly, the stack becomes [6, 8].

3. In the basic idea, we mentioned trying all possible length i. If we create max number for different i from scratch each time, that would be a waste of time. Suppose num = [4, 9, 3, 2, 1, 8, 7, 6], we need to create max number with length from 1 to 8. For i==8, result is the original array. For i==7, we need to drop 1 number from array, since 9 > 4, we drop 4, the result is [9, 3, 2, 1, 8, 7, 6]. For i==6, we need to drop 1 more number, 3 < 9, skip, 2 < 3, skip, 1 < 2, skip, 8 > 1, we drop 1, the result is [9, 3, 2, 8, 7, 6]. For i==5, we need to drop 1 more, but this time, we needn't check from beginning, during last scan, we already know [9, 3, 2] is monotonically non-increasing, so we check 8 directly, since 8 > 2, we drop 2, the result is [9, 3, 8, 7, 6]. For i==4, we start with 8, 8 > 3, we drop 3, the result is [9, 8, 7, 6]. For i==3, we start with 8, 8 < 9, skip, 7 < 8, skip, 6 < 7, skip, by now, we've got maximum number we can create from num without length constraint. So from now on, we can drop a number from the end each time. The result is [9, 8, 7], For i==2, we drop last number 7 and have [9, 8]. For i==1, we drop last number 8 and have [9].

```java
public int[] maxNumber(int[] nums1, int[] nums2, int k) {
    int n = nums1.length;
    int m = nums2.length;
    int[] ans = new int[k];
    for (int i = Math.max(0, k - m); i <= k && i <= n; ++i) {
        int[] candidate = merge(maxArray(nums1, i), maxArray(nums2, k - i), k);
        if (greater(candidate, 0, ans, 0)) ans = candidate;
    }
    return ans;
}
private int[] merge(int[] nums1, int[] nums2, int k) {
    int[] ans = new int[k];
    for (int i = 0, j = 0, r = 0; r < k; ++r)
        ans[r] = greater(nums1, i, nums2, j) ? nums1[i++] : nums2[j++];
    return ans;
}
public boolean greater(int[] nums1, int i, int[] nums2, int j) {
    while (i < nums1.length && j < nums2.length && nums1[i] == nums2[j]) {
        i++;
        j++;
    }
    return j == nums2.length || (i < nums1.length && nums1[i] > nums2[j]);
}
public int[] maxArray(int[] nums, int k) {
    int n = nums.length;
    int[] ans = new int[k];
    for (int i = 0, j = 0; i < n; ++i) {
        while (n - i + j > k && j > 0 && ans[j - 1] < nums[i]) j--;
        if (j < k) ans[j++] = nums[i];
    }
    return ans;
}
```

CPP　version, to be continue.

```cpp
class Solution {
public:
    vector<int> MaxSubVec(const vector<int> & nums, const std::size_t n) {
       if (nums.size() < n || 0 == n) return vector<int>();

          vector<int> reval;
          std::size_t remain(nums.size());
          for (int num : nums) {
            while (reval.size() + remain > n && !reval.empty() && reval.back() < num) {
              //printVector(reval);
              reval.pop_back();
            }

            reval.emplace_back(num);

            if (remain > 0) -- remain;
          }

          while (reval.size() > n) reval.pop_back();

          return reval;
    }
    
    bool GreaterThan(const std::vector<int> & left, 
         std::size_t i, 
         const std::vector<int> & right, 
         std::size_t j) {
        const std::size_t left_size(left.size()), right_size(right.size());
        while (i<left_size && j<right_size && left[i] == right[j]) {
            ++i;
            ++j;
        }
        return j == right_size || ( i < left_size && left[i] > right[j]); 
    }
    
    vector<int> Merge(const vector<int> & left, const vector<int> & right, std::size_t k) {
        vector<int> reval(k, 0);
        for (std::size_t i = 0, l = 0, r = 0; i < k; ++i) {
            reval[i] = GreaterThan(left,l,right,r) ? left[l++] : right[r++];
        }
        return reval;
    }
    
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        std::size_t size1(nums1.size()), size2(nums2.size());
        vector<int> reval(k,0);
        for (std::size_t i = 1; i < k && i < size1; ++i) {
            const vector<int> & left = MaxSubVec(nums1,i);
            const vector<int> & right = MaxSubVec(nums2,k - i);
            vector<int> temp = Merge(left, right, k);
            if (GreaterThan(temp,0,reval,0)) {
                reval = temp;
            }
        }
        return reval;
    }
    
};
```
