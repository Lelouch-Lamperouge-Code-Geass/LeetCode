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


If you have n identical tasks and need to separate by k steps, it needs ```(k+1)*(n-1) + 1``` steps. If you have m tasks all appear n times, it would take ```(k+1)*(n-1) + m``` when m <= k. All other tasks should be able to fill in the empty steps.

If all empty steps are filled out, then we do not need empty steps, the overall cost would be the size of input tasks.

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
        
        std::size_t reval = (n + 1) * (max_freq - 1);
        
        for (const std::pair<char, std::size_t> &item : task_freq_mapper) {
            if (item.second == max_freq) ++ reval;
        }
        
        return std::max(reval, tasks.size());
    }
};
```

