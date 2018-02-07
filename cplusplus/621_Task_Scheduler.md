Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

##### Example 1:

```
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
```

#### Note:

1. The number of tasks is in the range [1, 10000].
2. The integer n is in the range [0, 100].

# Solution

If you have t identical tasks and need to separate by n steps, it needs ```(n+1)*(t-1) + 1``` steps. Similar to problem "plant t trees every n meters". 

Now if we have m tasks with highest frequency, and same task are required to be at least n steps away, then it would take ```(n+1)*(max_freq-1) + num_of_chars_has_max_freq``` when ```max_freq <= n```. We basically here use tasks with max frequency to make frame, here ```n + 1``` is the frame size, and ```max_freq-1``` is the number of frames we initially used. And we still need to add the number of chars which has ```max_freq``` into our minimal size. 

Now we have a total size with ```(n + 1) * (max_freq - 1) + num_of_chars_has_max_freq```.

When ```max_freq <= n```, all other tasks with lower frequency will just fill the empty spaces.

When ```max_freq > n```, there will be no empty spaces left in the size we have so far, but all the tasks with lower frequency will just increase the gap if we fill them at end of each frame, and because their frequency is less than frame numbers we have, the gap between each same tasks will not be smaller for these tasks. In this case, we will find ```(n+1)*(max_freq-1) + num_of_chars_has_max_freq``` is smaller than ```tasks.size()```, and latter should be the return value. For example, we have AAABBBCCCDD, and k = 2. Firstly we arrange sth like ABCABCABC, but we still got 2 "D"s remained.So now we simply insert each 'D' to the end of each "ABC" sequence, and generate the asnwer ABCDABCDABC. That is to say, if we get ```num_of_chars_has_max_freq > k```, by applying such strategy, in the end we will have a sequence without idle, so the final answer is the size of the input array.

The idea is pretty simple. for example, you have (aaaabbbbcccddeef, 4) how would you do it:

```
0. Count how many occurrences of each character: a:4, b:4, c:3, d:2, e:1 
1. put the most 2 characters (ab) at least k apart first as reference point:
abXXabXXabXXab (X is empty position)
2. then fill the gap with all other numbers from most frequency to least frequency 
   like filling out a rotated array:
   
   2.1 fill with c first:  abCXabCXabCXab
   2.2 fill with d then: abcDabcDabcXab
   2.3 fill with e:    abcdEabcdabcEab    // Here, first E is actually put last, second E is put first, 
                                          //  because we are filling gaps in rotated manner. 
                                          // Note, it doesn't matter if it runs out of empty space, 
                                          // just insert E after abcd anyway, it won't break anything;
   2.4 fill with f:   abcdeabcdfabceab // A valid solution is generated.

3. Finally, how to determine if there is a solution:
    It's easy: At step 2, if you can't fill all the all empty positions 
    with remaining characters after step 1, there is no solution.

```
```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        std::unordered_map<char, std::size_t> task_freq_mapper;
        std::size_t max_freq(0);
        for (const char task : tasks) {
            ++ task_freq_mapper[task];
            max_freq = std::max(max_freq, task_freq_mapper[task]);
        }
        
        // Here "n + 1" is the frame size, "max_freq - 1" is the number of frames
        // we initialized. For example, for "AAAABBBBCC" with n == 2, 
        // the frame size is 3 and the number of frames is 3.
        // This is enough for us to put down "AB_AB_AB_".
        std::size_t reval = (n + 1) * (max_freq - 1);
        
        // Continue with above example, we still have "AB" left.
        // So after this we will have "AB_AB_AB_AB"
        // As for "CC", they will just fill the gap, "ABCABCAB_AB"
        for (const std::pair<char, std::size_t> &item : task_freq_mapper) {
            if (item.second == max_freq) ++ reval;
        }
        
        return std::max(reval, tasks.size());
    }
};
```

