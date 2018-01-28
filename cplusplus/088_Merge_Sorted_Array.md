Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.

# Solution
__You need confirm with interviewer that m + n is within integer range.__


_Note the in below code we merge backwards from i = m + n + 1 to i = 0, not merge forwards from i = 0 to i = m + n + 1.
The reason is that former will not override the numbers in nums1 that are not allocated yet._

For example,

```
nums1 : 1, 4, 5, _, _
nums2 : 2, 3
```

Write 5. 

```
nums1 : 1, 4, 5, _, 5
nums2 : 2, 3
```

Write 4.

```
nums1 : 1, 4, 5, 4, 5
nums2 : 2, 3
```

Write 3.

```
nums1 : 1, 4, 3, 4, 5
nums2 : 2, 3
```
Write 2.

```
nums1 : 1, 2, 3, 4, 5
nums2 : 2, 3
```

Write 1.

```
nums1 : 1, 2, 3, 4, 5
nums2 : 2, 3
```

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int index1(m - 1), index2(n - 1);
        for (int i = m + n - 1; i >= 0; --i) {
            if (index1 < 0) {
                nums1[i] = nums2[index2--];
            } else if (index2 < 0) {
                nums1[i] = nums1[index1--];
            } else {
                if (nums1[index1] > nums2[index2]) {
                    nums1[i] = nums1[index1--];
                } else {
                    nums1[i] = nums2[index2--];
                }
            }
        }
    }
};
```
