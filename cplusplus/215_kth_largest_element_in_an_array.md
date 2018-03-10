Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ? k ? array's length.

# Solution  

We can come up with some O(NlogN) solutions very easily.

* We can sort the array, and return k-th element.
* We can use a k-size min-heap, keep adding larger number into it and keep popping the smallest number out of it. Finally return the top element.

How can we implement a O(N) solution?

We recall that a partition algorithm can partition an array into three parts, the part larger than/equals to/smaller than a random number, and the return value is the final index where that random number is located.

Let's say if the return index is ```k - 1```(here kth is 1-based), then we already find out our target number.

But what if the return index is larger than ```k - 1```? That means the number we are looking for is at the left side of this index. Then all we need to do in this case is to find another random number within the left part and to partition again on the left range.

Same if the return index is smaller than ```k - 1```, which means the number we are looking for is at the right side of the returned index.

We keep doing partition, and each time we can "throw away" part of the input array.

Average time complexity is O(N), worst case(for example, when numbers are all the same) is O(N^2).
  
### Solution one

In quicksort, in each iteration, we need to select a pivot and then partition the array into three parts:

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

#### time complexity analysis

We know that for the while loop in ```findKthLargest```, we increase start or decrease end on every loop step, and this can take n steps. For ```randomPartition```, if all the numbers in the vector are the same, then the randomization is basically useless here, and it's time complexity is O(end + 1 - start).

So we know that in worst case(all numbers are the same), the time complexity is O(N^2).

Right now let's take analyze ```randomPartition``` which is a little tricky here.

The best case is that ```randomPartition``` can discard half of the numbers every time, this is the biggest difference between this problem and quick-sort algorithm. For quick-sort, the problem can be shown as this picture.

<img src = "https://ka-perseus-images.s3.amazonaws.com/21cd0d70813845d67fbb11496458214f90ad7cb8.png" height = "300" width = "300">

We know that the tree height in this picture is log(N), which means there are log(N) tree layers, and on each layer we process every element, so the best time complexity for quick-sort is O(NlogN).

However, in this problem, in best case we can discard half the elements every time after calling ```randomPartition```, thus we will call ```randomPartition``` log(N) times.

__The algorithm has average O(N) time, but worst case is O(N^2).__
  
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

In C++, ```std::nth_element``` is a partial sorting algorithm that rearranges elements in [first, last) such that:

* The element pointed at by nth is changed to whatever element would occur in that position if [first, last) was sorted.
* All of the elements before this new nth element are less than or equal to the elements after the new nth element.

```cpp
template< class RandomIt, class Compare >
void nth_element( RandomIt first, RandomIt nth, RandomIt last, Compare comp );
```

Here ```comp```	is acomparison function object (i.e. an object that satisfies the requirements of Compare) which returns true if the first argument is less than (i.e. is ordered before) the second. 

The signature of the comparison function should be equivalent to the following:

```cpp
 bool cmp(const Type1 &a, const Type2 &b);
```

The signature does not need to have const &, but the function object must not modify the objects passed to it.

The types Type1 and Type2 must be such that an object of type RandomIt can be dereferenced and then implicitly converted to both of them. 

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

Ideally exactly the same should apply std::nth\_element but the ISO C++ 2011 standard has not tightened up the complexity requirements. So std::nth\_element could be O(N * N) in the worst case. This could be because in David Musser's original paper (see here) he did not mention what algorithm should be swapped to if QuickSelect goes bad.

In the worst case, the median-of-medians using groups of 5 could be used (I have seen a paper the recommended groups of 7 but cannot find it). So a quality implementation of std::nth\_element could use QuickSelect and swap to median-of-medians if partitioning goes bad. This would guarantee O(N) behaviour. QuickSelect can be improved by using sampling making the worst case unlikely but not impossible.
