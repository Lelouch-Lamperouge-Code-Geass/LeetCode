Given a collection of intervals, merge all overlapping intervals.

For example,
```
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
```

# Solution

The idea to solve this problem is to first sort the intervals according to their start field and then scan the intervals from head to tail and merge those that overlap.

For sorting the intervals according to their start field, we define a comparison function as follows.

```cpp
static bool comp(Interval interval1, Interval interval2) {
    return interval1.start < interval2.start;
}
```

Then all the intervals are sorted in the ascending order of start. Now we define a current interval cur and initialize it to be intervals[0]. Then we scan from intervals[1] to intervals[n - 1]. If it overlaps with cur, merge them; otherwise, add cur to res, update cur to be intervals[i] and move on with the merging process.

There are two required subroutines in the above process: isOverlap to tell whether two intervals overlap and mergeTwo to merge two overlapping intervals.

For isOverlap, since the intervals are sorted in ascending order of start, we simply need to guarantee that end of the left (with smaller start) interval is not less than start of the right (with larger start) interval.

For mergeTwo, just take the minimum of start and maximum of end of the two overlapping intervals and return a new interval with these two values.

The complete code is as follows, which should be self-explanatory.

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
    vector<Interval> merge(vector<Interval>& intervals) {
        static auto Comparator = [](const Interval & left, const Interval & right) {
            return left.start < right.start;
        };
        std::sort(intervals.begin(), intervals.end(), Comparator);
        vector<Interval> reval;
        vector<Interval>::const_iterator iter = intervals.begin(), END = intervals.end();
        
        while(iter != END) {
            if (!reval.empty() && reval.back().end >= iter->start) {
                reval.back().end = std::max(reval.back().end, iter->end);
            } else {
                reval.emplace_back(*iter);
            }
            
            ++ iter;
        }
        
        return reval;
    }
};
```


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
  vector<Interval> merge(vector<Interval>& intervals) {
    vector<Interval> reval;
    std::sort(intervals.begin(),intervals.end(),IntervalCompare());
    for (const Interval & interval : intervals) {
      if (!reval.empty() && reval.back().end>=interval.start) {
        reval.back().end = std::max(reval.back().end,interval.end);
      } else {
        reval.push_back(interval);
      }
    }
    return reval;
  }
private:
  class IntervalCompare {
  public:
    bool operator() (const Interval & left, const Interval & right) {
      return left.start < right.start;
    }
  };
};
```
