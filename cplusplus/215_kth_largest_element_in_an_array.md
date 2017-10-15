Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ? k ? array's length.

# Solution  
  
### Solution one
n quicksort, in each iteration, we need to select a pivot and then partition the array into three parts:

1. Elements smaller than the pivot;
2. Elements equal to the pivot;
3. Elements larger than the pivot.
  
Now, let's do an example with the array [3, 2, 1, 5, 4, 6] in the problem statement. Let's assume in each time we select the leftmost element to be the pivot, in this case, 3. We then use it to partition the array into the above 3 parts, which results in [1, 2, 3, 5, 4, 6]. Now 3 is in the third position and we know that it is the third smallest element. Now, do you recognize that this subroutine can be used to solve this problem?

In fact, the above partition puts elements smaller than the pivot before the pivot and thus the pivot will then be the k-th smallest element if it is at the k-1-th position. Since the problem requires us to find the k-th largest element, we can simply modify the partition to put elements larger than the pivot before the pivot. That is, after partition, the array becomes [5, 6, 4, 3, 1, 2]. Now we know that 3 is the 4-th largest element. If we are asked to find the 2-th largest element, then we know it is left to 3. If we are asked to find the 5-th largest element, then we know it is right to 3. So, in the average sense, the problem is reduced to approximately half of its original size, giving the recursion T(n) = T(n/2) + O(n) in which O(n) is the time for partition. This recursion, once solved, gives T(n) = O(n) and thus we have a linear time solution. Note that since we only need to consider one half of the array, the time complexity is O(n). If we need to consider both the two halves of the array, like quicksort, then the recursion will be T(n) = 2T(n/2) + O(n) and the complexity will be O(nlogn).

Of course, O(n) is the average time complexity. In the worst case, the recursion may become T(n) = T(n - 1) + O(n) and the complexity will be O(n^2).

Shuffle here avoid the worst case, so each partition will just eliminate a half the of the array and then search on the other half. Here the first partition will search in an array of length n but the second partition will only need to search on length n/2 since we remove the other half and third search will also remove the half of the n/2 again and ..., to sum them up we traversed 2*n at most to get the answer.

Now let's briefly write down the algorithm before writing our codes.

1. Initialize left to be 0 and right to be nums.size() - 1;
2. Partition the array, if the pivot is at the k-1-th position, return it (we are done);
3. If the pivot is right to the k-1-th position, update right to be the left neighbor of the pivot;
4. Else update left to be the right neighbor of the pivot.
5. Repeat 2.
  
Now let's turn it into code.
  
```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        std::size_t begin(0), end(nums.size() - 1);
        
        while (begin <= end) {
            std::size_t index = randomPartition(nums, begin, end);
            
            if (index + 1 == k) {
                return nums[index];
            } else if (index + 1 > k) {
                end = index - 1;
            } else { // index + 1 < k
                begin = index + 1;
            }
        }
        
        throw std::runtime_error("Invalid input!");
    }
private:
    
    // Partition the array between range [begin, end].
    // Choose a random index, make sure nums[begin, index) >= nums[index] >= nums(index, end].
    // Return the random index.
    std::size_t randomPartition(vector<int> &nums, std::size_t begin, std::size_t end) {
        std::size_t random_index = begin + rand() % (end + 1 - begin);
        
        const int pivot_value = nums[random_index];
        std::swap(nums[random_index], nums[end]);
        
        std::size_t i(begin - 1), j(begin);
        while (j < end) {
            if (nums[j] >= pivot_value) {
                ++ i;
                std::swap(nums[i], nums[j]);
            }
            
            ++ j;
        }
        
        ++ i;
        std::swap(nums[i], nums[j]);
        
        return i;
    }
};
```

### Solution two

```cpp
class Solution {
public:
  int findKthLargest(vector<int>& nums, int k) {
    std::nth_element(nums.begin(),nums.begin()+k-1,nums.end(),std::greater<int>());
    return nums[k-1];
  }
};
```

### Solution three
Other possibility is to use a min oriented priority queue that will store the K-th largest values. The algorithm iterates over the whole input and maintains the size of priority queue.

  __O(N lg K) running time + O(K) memory__

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; i++)
            pq.pop(); 
        return pq.top();
    }

};
```

# Knowledge

### std::nth_element implementations complexities

The expected running time is O(N) The worst case running time for most implemententations is O(N * N) because most implementations use QuickSelect and it could be that QuickSelect runs into bad partitions. 

Now with the new ISO C++ 2011 standard, the complexity for std::sort has been tightened up - it is guaranteed to be O(N * log N) and has no worse case as David Musser's IntroSort is used: - use QuickSort and if parts of the array experience bad partitioning, swap to heapsort.

Ideally exactly the same should apply std::nth_element but the ISO C++ 2011 standard has not tightened up the complexity requirements. So std::nth_element could be O(N * N) in the worst case. This could be because in David Musser's original paper (see here) he did not mention what algorithm should be swapped to if QuickSelect goes bad.

In the worst case, the median-of-medians using groups of 5 could be used (I have seen a paper the recommended groups of 7 but cannot find it). So a quality implementation of std::nth_element could use QuickSelect and swap to median-of-medians if partitioning goes bad. This would guarantee O(N) behaviour. QuickSelect can be improved by using sampling making the worst case unlikely but not impossible.
