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
