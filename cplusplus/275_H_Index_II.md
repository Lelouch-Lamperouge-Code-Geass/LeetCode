Follow up for [H-Index](https://leetcode.com/problems/h-index/description/): What if the citations array is sorted in ascending order? Could you optimize your algorithm?

# Solution

__Note that the citation vector here is different from the counting-sort style citation vector in LeetCode 274, in the latter the counting-sort style citation vector is increasing continuously, but here the citation vector is not. Another difference is that in the counting-sort style citation vector whose indexes represting citation times, are obviously unique. So if you want to use the same method as LeetCode 274, you need create the counting-sort style citation vector too.__

Now let's think an alternative solution.


The basic idea of this solution is to use binary search to find the minimum index such that

```
citations[index] >= length(citations) - index
```

After finding this index, the answer is length(citations) - index.

This logic is very similar to the C++ function lower_bound or upper_bound.
                        
We use two pinter to solve this problem: pointer l (low) and pointer h (high).

Say n = citations.length.
Because the range of H-index is [0,n], at the beginning we must point high pointer after the last element of the array: h = n. In this way we can generate all possible value without worrying about annoying corner case.

The rest is standard binary search, we find middle point m and compare citations[m] with n-m (n-m means number of papers has at least citations[m] citations.)

1. citations[m] == n-m : we find the answer
2. citations[m] < n-m : more papers has at least this number of citations we should raise the bar of citations so we go to the right part: l = m+1.
3. citations[m] > n-m : we should lower the bar so we go to the left part: h = m.

In the end l == r and the H-index is n-l. 

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        // In the citations vector, we can say that each index
        // represent paper_id. And the corresponding value represents
        // the citations of that paper.
        int n_size(citations.size()),low(0), high(n_size-1);
        while (low <= high) {
            int mid = low + (high-low) / 2;
            int paper_num = n_size - mid;
            if (paper_num < citations[mid]) { 
                // We need decrease the expecting citation value, since there
                // are not enough papers meet current citation requirement.
                high = mid - 1;
            } else if (paper_num > citations[mid]) {
                // We have enough papers to meet current citation requirement,
                // but maybe there is a bigger citation value which is bigger than
                // current citation value but still less than paper_num.
                low = mid + 1;
            } else { // paper_num == citations[mid]) 
                return paper_num;
            } 
        }
        
        // Here low > high.
        // Note that here the low and high are paper_id,
        // they don't have direct relationship with H-Index.
        return n_size - low;
    }
};
```

# Summary

The key to solve problem 274 and 275 is based on the defination of H-Index, "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

We need to set up a relationship between citation and the number of papers meet that citation. In 274, the counting-sort vector's indexes represent the citation, and values represent the number of papers meeting the citation times. In 275, the sorted-citation vecotr's indexes represent the id of paper and values represent the citation for that paper, but we can get the number of pappers by using ```n - index```.

