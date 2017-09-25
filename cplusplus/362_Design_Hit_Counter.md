Design a hit counter which counts the number of hits received in the past 5 minutes.

Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made to the system in chronological order (ie, the timestamp is monotonically increasing). You may assume that the earliest timestamp starts at 1.

It is possible that several hits arrive roughly at the same time.

# Solution
  
O(s) s is total seconds in given time interval, in this case 300.
basic ideal is using buckets. 1 bucket for every second because we only need to keep the recent hits info for 300 seconds. hit[] array is wrapped around by mod operation. Each hit bucket is associated with times[] bucket which record current time. If it is not current time, it means it is 300s or 600s... ago and need to reset to 1.

```cpp
class HitCounter {
public:
  /** Initialize your data structure here. */
  HitCounter() {
    times.resize(300);
    hits.resize(300);
  }

  /** Record a hit.
      @param timestamp - The current timestamp (in seconds granularity). */
  void hit(int timestamp) {
    int idx = timestamp % 300;
    if (times[idx] != timestamp) {
      times[idx] = timestamp;
      hits[idx] = 1;
    } else {
      ++hits[idx];
    }
  }

  /** Return the number of hits in the past 5 minutes.
      @param timestamp - The current timestamp (in seconds granularity). */
  int getHits(int timestamp) {
    int res = 0;
    for (int i = 0; i < 300; ++i) {
      if (timestamp - times[i] < 300) {
        res += hits[i];
      }
    }
    return res;
  }

private:
  vector<int> times, hits;
};
```
