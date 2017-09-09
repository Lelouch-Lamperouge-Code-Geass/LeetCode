Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.

# Solution
__You need confirm with interviewer that m + n is within integer range.__


Note the in below code we merge backwards from i = m + n + 1 to i = 0, not merge forwards from i = 0 to i = m + n + 1.
The reason is that former will not override the numbers in nums1 we have not allocate.

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i1(m-1),i2(n-1);
        for (int i=m+n-1;i>=0;--i) {
            if(i2<0) nums1[i] = nums1[i1--];
            else if(i1<0) nums1[i] =nums2[i2--];
            else nums1[i] = nums1[i1] > nums2[i2] ? nums1[i1--] : nums2[i2--]; 
        }
    }
};
```
