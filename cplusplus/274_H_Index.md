Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.
  
# Solution

### Solution 1

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/d/da/H-index-en.svg/300px-H-index-en.svg.png)
  
Time complexity O(nlogn), space complexity O(1).
  
```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        // Sort in descending order
        std::sort(citations.begin(), citations.end(), std::greater<int>());
        
        std::size_t pos(0);
        while (pos < citations.size() && citations[pos] > pos) {
            ++ pos;
        }
        
        return pos;
    }
};
```

### Solution 2

This type of problems always throw me off, but it just takes some getting used to. The idea behind it is some bucket sort mechanisms. First, you may ask why bucket sort. Well, the h-index is defined as the number of papers with reference greater than the number. So assume n is the total number of papers, if we have n+1 buckets, number from 0 to n, then for any paper with reference corresponding to the index of the bucket, we increment the count for that bucket. The only exception is that for any paper with larger number of reference than n, we put in the n-th bucket.

Then we iterate from the back to the front of the buckets, whenever the total count exceeds the index of the bucket, meaning that we have the index number of papers that have reference greater than or equal to the index. Which will be our h-index result. The reason to scan from the end of the array is that we are looking for the greatest h-index. For example, given array [3,0,6,5,1], we have 6 buckets to contain how many papers have the corresponding index. Hope to image and explanation help.

![alt](http://i67.tinypic.com/2yvpfv5.jpg)
       
Time complexity O(n), space complexity O(n).

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int num_of_papers(citations.size());
        
        // Here the indexes are the citation times,
        // the values store how many papers have that specific citation times.
        vector<int> citations_count(num_of_papers + 1, 0);
        
        for (int cita : citations) {
            if (cita > num_of_papers) { 
                // We know that the H-index will not be larger than
                // the number of papers, so for citation larger than number of papers,
                // we can just count it into the last counter.
                ++ citations_count[num_of_papers];
            } else {
                ++ citations_count[cita];
            }
        }
        
        // Here paper_count_so_far will keep increasing, 
        // untill it is not less than i, i here means the citation times.
        // We need to find the first i(citation times) which is not bigger than
        // the paper_count_so_far.
        int paper_count_so_far(0);
        for (int i = num_of_papers; i >= 0; --i) {
            paper_count_so_far += citations_count[i];
            if (paper_count_so_far >= i) {
                return i;
            }
        }
        
        return 0;
    }
};
```

  
