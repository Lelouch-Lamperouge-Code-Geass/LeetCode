Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example:
(1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6]. 
(2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].

##### Note:
You may assume all input has valid answer.

##### Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?

# Solution

### Solution 1

The idea is : we partition nums into small part and big part. And we add numbers from big part into odd indexes, and numbers from small part into even indexes. Note that for both part we need begin with their respective highest index, because the largest numbers in small part may be the same as the smallest numbers in big part.

We need to implement three-way-parition here because the std::nth_element function in LeetCode isn't implemented with three-way-partition. However, in some C++ compiler(e.g. my visual studio) it is.

The purpose of three-way-partition is to gurantee that the elements in nums is arranged into three clusters : smaller, equals, bigger.

```cpp
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        int mid = n/2;
        nth_element(nums.begin(), nums.begin() + mid, nums.end());
        threeWayPartition(nums, nums[mid]);
        vector<int> res(n);
        
        // Here for both large part and small part,
        // we begin with the highest index in their part.
        // This is because it is possible that the largest numbers
        // in small part are the same as the smallest numbers in big part.
        // And thus we cant interlace them at last.
        int largeStart = n-1;
        int smallStart = (n%2) ? mid : (mid-1);
        for (int i = 0; i < n; i+=2)
            res[i] = nums[smallStart--];
        for (int i = 1; i < n; i+=2)
            res[i] = nums[largeStart--];
        nums = res;
    }
    
    // this ensures all values equal to the median is in the middle.
    // Smaller numbers come before that, and bigger numbers come after that.
    void threeWayPartition(vector<int> &nums, int val) {
        int i = 0, j = 0;
        int n = nums.size()-1;
        while (j <= n){
            if (nums[j] < val)
                swap(nums[i++], nums[j++]);
            else if (nums[j] > val)
                swap(nums[j], nums[n--]);
            else
                j++;
        }
    }
};
```

### Solution 2
The intuitive solution to this problem is to split numbers into a smaller half and a bigger half.
And then get number from smaller array and bigger array alternately.
How can we do better to get O(1) space complexity?
Then we have to perform the reconstruction in-place.
We know that we can use partition algorithm to make an array with half smaller and half bigger.
Here we can use three-way partitioning to arrange the numbers so that
those larger than the median come first, then those equal to the median come next,
and then those smaller than the median come last.
It is called three-way partition because original partition algorithm divide the array into bigger and smaller array, while three-way 
partition divides the array into bigger, equal, smaller array.
We just need to twist it a little bit to make numbers wiggle.
Make the partition results's indices [0, 1, 2, ... , n - 1, n] mapped to [1, 3, 5, ... , 0, 2, 4, ...].

First I find a median using nth_element. That only guarantees O(n) average time complexity and I don't know about space complexity. I might write this myself using O(n) time and O(1) space, but that's not what I want to show here.

This post is about what comes after that. We can use three-way partitioning to arrange the numbers so that those larger than the median come first, then those equal to the median come next, and then those smaller than the median come last.

Ordinarily, you'd then use one more phase to bring the numbers to their final positions to reach the overall wiggle-property. But I don't know a nice O(1) space way for this. Instead, I embed this right into the partitioning algorithm. That algorithm simply works with indexes 0 to n-1 as usual, but sneaky as I am, I rewire those indexes where I want the numbers to actually end up. The partitioning-algorithm doesn't even know that I'm doing that, it just works like normal (it just uses A(x) instead of nums[x]).

Let's say nums is [10,11,...,19]. Then after nth_element and ordinary partitioning, we might have this (15 is my median):

```
index:     0  1  2  3   4   5  6  7  8  9
number:   18 17 19 16  15  11 14 10 13 12
```

I rewire it so that the first spot has index 5, the second spot has index 0, etc, so that I might get this instead:
```
index:     5  0  6  1  7  2  8  3  9  4
number:   11 18 14 17 10 19 13 16 12 15
```
And 11 18 14 17 10 19 13 16 12 15 is perfectly wiggly. And the whole partitioning-to-wiggly-arrangement (everything after finding the median) only takes O(n) time and O(1) space.

First I find a median using nth_element. That only guarantees O(n) average time complexity and I don't know about space complexity. I might write this myself using O(n) time and O(1) space, but that's not what I want to show here.

This post is about what comes after that. We can use three-way partitioning to arrange the numbers so that those larger than the median come first, then those equal to the median come next, and then those smaller than the median come last.

Ordinarily, you'd then use one more phase to bring the numbers to their final positions to reach the overall wiggle-property. But I don't know a nice O(1) space way for this. Instead, I embed this right into the partitioning algorithm. That algorithm simply works with indexes 0 to n-1 as usual, but sneaky as I am, I rewire those indexes where I want the numbers to actually end up. The partitioning-algorithm doesn't even know that I'm doing that, it just works like normal (it just uses A(x) instead of nums[x]).

Let's say nums is [10,11,...,19]. Then after nth_element and ordinary partitioning, we might have this (15 is my median):

index:     0  1  2  3   4   5  6  7  8  9
number:   18 17 19 16  15  11 14 10 13 12
I rewire it so that the first spot has index 5, the second spot has index 0, etc, so that I might get this instead:

index:     5  0  6  1  7  2  8  3  9  4
number:   11 18 14 17 10 19 13 16 12 15
And 11 18 14 17 10 19 13 16 12 15 is perfectly wiggly. And the whole partitioning-to-wiggly-arrangement (everything after finding the median) only takes O(n) time and O(1) space.

If the above description is unclear, maybe this explicit listing helps:

```
Accessing A(0) actually accesses nums[1].
Accessing A(1) actually accesses nums[3].
Accessing A(2) actually accesses nums[5].
Accessing A(3) actually accesses nums[7].
Accessing A(4) actually accesses nums[9].
Accessing A(5) actually accesses nums[0].
Accessing A(6) actually accesses nums[2].
Accessing A(7) actually accesses nums[4].
Accessing A(8) actually accesses nums[6].
Accessing A(9) actually accesses nums[8].
```

```cpp
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        const std::size_t nums_size(nums.size());

        // Find position in the middle.
        // Note that it is not median, because it doesn't take average value when length is an even number.
        // Also we use nth_element here only to find the 'mid' value as well as partition nums.
        std::vector<int>::iterator pivot_pos = nums.begin() + nums_size / 2;
        std::nth_element(nums.begin(), pivot_pos, nums.end()); 
        const int pivot = *pivot_pos;
        
        // A functor to get wiggle index
        auto getWiggleIndex = [nums_size](int idx) { return (2 * idx + 1) % (nums_size | 1); };
        
        // [0, left] : numbers larger than pivot
        // (left, mid] : numbers equal to pivot
        // [right, ) : numbers smaller than pivot
        std::size_t left(-1), mid(0), right(nums_size);
        
        while (mid < right) {
            if (nums[getWiggleIndex(mid)] > pivot) {
                // we can move mid forward here because we know all the number between [0, mid]
                // are not smaller than pivot
                std::swap(nums[getWiggleIndex(++left)], nums[getWiggleIndex(mid++)]);
            } else if (nums[getWiggleIndex(mid)] < pivot) {
                // can't ++mid here because we know nothing about nums[right]
                std::swap(nums[getWiggleIndex(mid)], nums[getWiggleIndex(--right)]); 
            } else { // == pivot
                ++ mid;
            }
        }       
    }
};
```

#### Highlight

The intuitive solution to this problem is to split numbers into a smaller half and a bigger half.
And then fill the original vector with numbers from smaller array and bigger array alternately.

To split the numbers into bigger and smaller halves, we need use partition algorithm.
The tricky thing here is how to fill the vector  "in a wiggle way" after that?

One way is to do an index mapping which can build a mapping relationship "index => mapping index". If the space complexity requirement is not constant, this is easy. While in order to have O(1) space complexity, swapping index after partition might be very hard. 

Therefore, in this solution, we do the index mapping during partition.

You also need to now that std::nth_element internally uses parition algorithm as well. It's time complexisty is on average O(N), and the worse time complexity is depend on what c++ version you are using, could be O(N) or O(N^2).


In fact, if nth_element is implemented with __three-way partition__ and we don't need to have O(1) space complexity, we can simply use below solution.


```cpp
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        const std::size_t nums_size = nums.size();
        std::vector<int>::iterator pivot_pos = nums.begin() + nums.size() / 2;
        std::nth_element(nums.begin(), pivot_pos, nums.end(), std::greater<int>());
        const int pivot = *pivot_pos;
        
        std::size_t n = nums.size(), mid_pos = nums.size() / 2;
        
        // A functor to get wiggle index
        auto virtualIndex = [nums_size](int idx) { return (2 * idx + 1) % (nums_size | 1); };
        
        vector<int> copy = nums;
        
        for (std::size_t i = 0; i < nums_size; ++i) {
            copy[virtualIndex(i)] = nums[i];
        }
        
        nums = copy;
    }
};
```


However, it seems like nth_element is not implemented in three-way parition, so.....


# Knowledge

### Dutch national flag problem

The Dutch national flag problem (DNF) is a computer science programming problem proposed by Edsger Dijkstra. The flag of the Netherlands consists of three colors: red, white and blue. Given balls of these three colors arranged randomly in a line (the actual number of balls does not matter), the task is to arrange them such that all balls of the same color are together and their collective color groups are in the correct order.

The solution to this problem is of interest for designing sorting algorithms; in particular, variants of the quicksort algorithm that must be robust to repeated elements need a three-way partitioning function that groups items less than a given key (red), equal to the key (white) and greater than the key (blue). Several solutions exist that have varying performance characteristics, tailored to sorting arrays with either small or large numbers of repeated elements.

#### The array case

This problem can also be viewed in terms of rearranging elements of an array. Suppose each of the possible elements could be classified into exactly one of three categories (bottom, middle, and top). For example, if all elements are in 0 ... 1, the bottom could be defined as elements in 0 ... 0.1 (not including 0.1), the middle as 0.1 ... 0.3 (not including 0.3) and the top as 0.3 and greater. (The choice of these values illustrates that the categories need not be equal ranges). The problem is then to produce an array such that all "bottom" elements come before (have an index less than the index of) all "middle" elements, which come before all "top" elements.

One algorithm is to have the top group grow down from the top of the array, the bottom group grow up from the bottom, and keep the middle group just above the bottom. The algorithm indexes three locations, the bottom of the top group, the top of the bottom group, and the top of the middle group. Elements that are yet to be sorted fall between the middle and the top group. At each step, examine the element just above the middle. If it belongs to the top group, swap it with the element just below the top. If it belongs in the bottom, swap it with the element just above the bottom. If it is in the middle, leave it. Update the appropriate index. Complexity is Θ(n) moves and examinations.


#### Pseudocode

The following pseudocode for three-way partitioning assumes zero-based array indexing. It uses three indices i, j and n, maintaining the invariant that i ≤ j. n holds the boundary of numbers greater than mid. j is the position of number under consideration. And i is the boundary for the numbers lesser than the mid.

```
procedure three-way-partition(A : array of values, mid : value):
    i ← 0
    j ← 0
    n ← size of A - 1

    while j ≤ n:
        if A[j] < mid:
            swap A[i] and A[j]
            i ← i + 1
            j ← j + 1
        else if A[j] > mid:
            swap A[j] and A[n]
            n ← n - 1
        else:
            j ← j + 1
```
