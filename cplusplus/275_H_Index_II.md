Follow up for [H-Index](https://leetcode.com/problems/h-index/description/): What if the citations array is sorted in ascending order? Could you optimize your algorithm?

# Solution
 
![alt](https://upload.wikimedia.org/wikipedia/commons/d/da/H-index-en.svg)

Look at above chart, the difference from this description is that the citations array is sorted in __descending order__ in this chart.

                        
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
        int n_size(citations.size()),low(0), high(n_size-1);
        while (low <= high) {
            int mid = low + (high-low) / 2;
            int paper_num = n_size - mid;
            if (paper_num < citations[mid]) { 
                high = mid - 1;
            } else if (paper_num > citations[mid]) {
                low = mid + 1;
            } else { // paper_num==citations[mid]) {
                return paper_num;
            } 
        }
        return n_size-low;
    }
};
```
