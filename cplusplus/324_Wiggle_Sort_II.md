Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example:
(1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6]. 
(2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].

##### Note:
You may assume all input has valid answer.

##### Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?

# Solution
The intuitive solution to this problem is to split numbers into a smaller half and a bigger half.
And then get number from smaller array and bigger array alternately。
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
