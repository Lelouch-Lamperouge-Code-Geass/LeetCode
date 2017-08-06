Follow up for [H-Index](https://leetcode.com/problems/h-index/description/): What if the citations array is sorted in ascending order? Could you optimize your algorithm?

# Solution
  
                        
Just binary search, each time check citations[mid]  :
                        
* case 1: citations[mid] == len-mid, then it means there are citations[mid] papers that have at least citations[mid] citations.  
* case 2: citations[mid] > len-mid, then it means there are citations[mid] papers that have moret than citations[mid] citations, so we should continue searching in the left half  
* case 3: citations[mid] < len-mid, we should continue searching in the right side

After iteration, it is guaranteed that right+1 is the one we need to find (i.e. len-(right+1) papars have at least len-(righ+1) citations)  

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n_size(citations.size()),low(0), high(n_size-1);
        while (low<=high) {
            int mid = low + (high-low) / 2;
            int paper_num = n_size - mid;
            if (paper_num==citations[mid]) {
                return paper_num;
            } else if (paper_num<citations[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return n_size-low;
    }
};
```
