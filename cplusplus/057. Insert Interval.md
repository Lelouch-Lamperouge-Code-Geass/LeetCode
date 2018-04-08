Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:

```
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
```

Example 2:

```
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
```

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].

# Solution

Note that here the existing intervals are non-overlapping, so all we need to consider is how to add the new interval.

If the existing intervals are overlapping, the solution will be different.

You need pay attention to this kind of detail before dive into solving the problem.

```cpp

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> reval;
        vector<Interval>::iterator iter = intervals.begin(), END = intervals.end();
        
        // Skip all previous intervals
        while (iter != END && iter->end < newInterval.start) {
            reval.emplace_back(*iter);
            ++ iter;
        } 
        
        // Merge interval
        while (iter != END && iter->start <= newInterval.end) {
            newInterval.start = std::min(newInterval.start, iter->start);
            newInterval.end = std::max(newInterval.end, iter->end);
            ++ iter;
        }
        
        reval.emplace_back(newInterval);
        
        // Copy the rest intervals 
        reval.insert(reval.end(), iter, END);
        
        return reval;
    }
};

```
