Given a collection of intervals, merge all overlapping intervals.

For example,
```
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
```

# Solution

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
