Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

For example, Given [[0, 30],[5, 10],[15, 20]], return false.

# Solution

The idea is pretty simple: first we sort the intervals in the ascending order of start; then we check for the overlapping of each pair of neighboring intervals. If they do, then return false; after we finish all the checks and have not returned false, just return true.

Sorting takes O(nlogn) time and the overlapping checks take O(n) time, so this idea is O(nlogn) time in total.

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
    bool canAttendMeetings(vector<Interval>& intervals) {
        static auto Compare = [](const Interval &left, const Interval &right){
            return left.start < right.start;
        };
        
        std::sort(intervals.begin(), intervals.end(), Compare);
        
        int pre_end(INT_MIN);
        for (const Interval &inter : intervals) {
            if (inter.start < pre_end) {
                return false;
            }
            pre_end = inter.end; // We don't need to use std::max here since pre_end <= inter.end for sure
        }
        
        return true;
    }
};
```
