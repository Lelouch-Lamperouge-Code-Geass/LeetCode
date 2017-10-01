You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

```
Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].
```    

# Solution

### Solution one

Every node will maintain a val sum recording the total of number on it's left bottom side, dup counts the duplication. For example, [3, 2, 2, 6, 1], from back to beginning,we would have:
```
        1(0, 1)
         \
         6(3, 1)
         /
       2(0, 2)
           \
            3(0, 1)
```
When we try to insert a number, the total number of smaller number would be adding dup and sum of the nodes where we turn right.
for example, if we insert 5, it should be inserted on the way down to the right of 3, the nodes where we turn right is 1(0,1), 2,(0,2), 3(0,1), so the answer should be (0 + 1)+(0 + 2)+ (0 + 1) = 4

if we insert 7, the right-turning nodes are 1(0,1), 6(3,1), so answer should be (0 + 1) + (3 + 1) = 5.

```cpp
class Solution {
private:
    struct TreeNode;
    typedef std::shared_ptr<TreeNode> TreeNodePtr;
    
    struct TreeNode {
        TreeNode(int value) : m_value(value), m_left_children(0),
                                           m_count(1), m_left(nullptr), m_right(nullptr) {}
        int m_value;
        int m_left_children; // recording the amount of left children
        int m_count; // recording the amount of duplicate numbers
        TreeNodePtr m_left, m_right;
    };
    
    // return the amount of previous smaller nodesm
    int Insert(TreeNodePtr & root, const int number) {
        if (!root) { 
            root = std::make_shared<TreeNode>(number);
            return 0;
        } else {
            if (number > root->m_value) {
                return root->m_left_children + root->m_count + Insert(root->m_right, number);
            }  else if (number < root->m_value){
                ++ root->m_left_children;
                return Insert(root->m_left, number);
            }  else { // equal
                ++ root->m_count;
                return root->m_left_children;
            }
        }
    }
    
public:
    vector<int> countSmaller(vector<int>& nums) {
            const std::size_t nums_size(nums.size());
            if (nums_size == 0) return vector<int>();
            vector<int> reval(nums_size, 0);
            TreeNodePtr root(nullptr);
            for (int i = nums_size - 1; i < nums_size; --i) {
                reval[i] = Insert(root, nums[i]);
            }
            return reval;
    }
};
```


### Solution Two

The smaller numbers on the right of a number are exactly those that jump from its right to its left during a stable sort. So I do mergesort with added tracking of those right-to-left jumps.

__The general mergesort is stable, quicksort is not stable.__

MergeSort-based solution is a standard way to solve problems related to inverse numbers.

Here is an example to illustrate the general idea of MergeSort-based algorithm:

Now we want to consider an array  ``` 6 4 1 8 7 5 2 9```.

First thing first, split the array into to subarrays:

```
6 4 1 8
7 5 2 9
```

and then calculate the inverse numbers within the group:

```
1 4(1) 6(1,4) 8
2 5(2) 7(2,5) 9
```

where the numbers in the parentheses are the numbers that should be counted when we calculate the inverse number.
Now we need to merge these two arrays into one sorted array. The first element to be put into the sorted destination array is the "1" in the first array.

```
 1                  4(1) 6(1,4) 8
                  2 5(2) 7(2,5) 9               merged elements in the 2nd array = ()
```

The second element to merge is the "2" in the second array:

```
 1 2                4(1) 6(1,4) 8
                    5(2) 7(2,5) 9               merged elements in the 2nd array = (2)

```

The third element to merge is the "4" in the first array:

```
 1 2 4(1,2)              6(1,4) 8
                    5(2) 7(2,5) 9               merged elements in the 2nd array = (2)

```

When we merge the "4(1)", we found that "4" is actually greater than all merged elements in the second array (i.e. [2]). Therefore, we also need to consider those elements. Therefore, the numbers in the parenthese of 2 become (1)+(2) = (1,2). Next step:

```
 1 2 4(1,2) 5(2)         6(1,4) 8
                         7(2,5) 9               merged elements in the 2nd array = (2,5)
```
 
Next (add the inverse number of element "6" by 2)

```
 1 2 4(1,2) 5(2) 6(1,4,2,5)     8
                         7(2,5) 9               merged elements in the 2nd array = (2,5)
```

So and so forth, finally reach

```
 1 2 4(1,2) 5(2) 6(1,4,2,5) 7(2,5) 8(2,5,7) 9
                                                merged elements in the 2nd array = (2,5,7,9)
```
 
Additionally, when we need to count the inverse number, we do not need to record the exact elements, we only need to record the numbers. So, we can use a variable to record the number of "merged elements in the 2nd array" (for example, semilen in the code beneath) and the number of smaller elements of each element (for example, results[idx] in the code beneath).

__Complexities: Time: O(n log n)    Space: O(n)__


```cpp
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        const std::size_t n = nums.size();
        vector<std::size_t> indexes(n, 0);
        std::iota (std::begin(indexes), std::end(indexes), 0);
        vector<int> count(n, 0);
        merge_sort_on_indexes(nums, indexes, count, 0, n);
        return count;
    }
private:
    void merge_sort_on_indexes(const vector<int> &nums,
                              vector<std::size_t> &indexes,
                              vector<int> &count,
                              std::size_t begin,
                              std::size_t end) {
        if (begin + 1< end) {
            std::size_t mid = begin + (end - begin) / 2;
            merge_sort_on_indexes(nums, indexes, count, begin, mid);
            merge_sort_on_indexes(nums, indexes, count, mid, end);
            merge_on_indexes(nums, indexes, count, begin, mid, end);
        }
    }
    
    // Notice here that since we are doing merge_sort on indexes,
    // 'begin', 'mid', 'end' here represent the index in 'indexes'.
    //  You can think 'indexes' as a mapping to original index.
    void merge_on_indexes(const vector<int> &nums,
                          vector<std::size_t> &indexes,
                          vector<int> &count,
                          std::size_t begin,
                          std::size_t mid,
                          std::size_t end) {
        vector<int> cache(end - begin, 0); // Store the merged indexes
        
        std::size_t index(0), left(begin), right(mid), added_right(0);
        while (left < mid && right < end) {
            if (nums[indexes[right]] < nums[indexes[left]]) {
                // When we are pushing elements in right array, we don't need to
                // update 'count' array, because the smaller count of right element
                // will stay the same when merging with left array.
                cache[index++] = indexes[right++];
                ++ added_right; // one smaller number added to cache
            } else {
                // When we are pushing elements in left array, we need update 
                // 'count' array with the count of smaller elements in right array
                // merged so far.
                count[indexes[left]] += added_right;
                cache[index++] = indexes[left++];
            }
        }
        
        while (right < end)  cache[index++] = indexes[right++];
        while (left < mid) {
            count[indexes[left]] += added_right;
            cache[index++] = indexes[left++];
        }
        
        for (std::size_t i = 0; i < end - begin; ++i) {
            indexes[begin + i] = cache[i];
        }
    }
};
```
