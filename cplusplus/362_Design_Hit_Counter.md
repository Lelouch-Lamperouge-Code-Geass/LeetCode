Design a hit counter which counts the number of hits received in the past 5 minutes.

Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made to the system in chronological order (ie, the timestamp is monotonically increasing). You may assume that the earliest timestamp starts at 1.

It is possible that several hits arrive roughly at the same time.

# Solution
  
O(s) s is total seconds in given time interval, in this case 300.
basic ideal is using buckets. 1 bucket for every second because we only need to keep the recent hits info for 300 seconds. hit[] array is wrapped around by mod operation. Each hit bucket is associated with times[] bucket which record current time. If it is not current time, it means it is 300s or 600s... ago and need to reset to 1.

```cpp
class HitCounter {
private:
    vector<int> bucket_timestamps;
    vector<int> bucket_hits;
public:
    /** Initialize your data structure here. */
    HitCounter() : bucket_timestamps(300, 0), bucket_hits(300, 0){
        
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        int index = timestamp % 300;
        if (bucket_timestamps[index] != timestamp) {
            // This bucket is older than 5 minutes
            bucket_timestamps[index] = timestamp;
            bucket_hits[index] = 1;
        } else {
            ++ bucket_hits[index];
        }
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        int reval(0);
        for (int i = 0; i < 300; ++i) {
            if (timestamp - bucket_timestamps[i] < 300) {
                reval += bucket_hits[i];
            }
        }
        return reval;
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter obj = new HitCounter();
 * obj.hit(timestamp);
 * int param_2 = obj.getHits(timestamp);
 */
```

However, this solution is not thread-safe.

Here is the thread-safe version.

```cpp
class HitCounter {
    vector<atomic<uint64_t>> hits;
    
public:
    HitCounter() : hits(300) {}
    
    void hit(uint32_t timestamp) {
        int bucket = timestamp % 300;
        uint64_t curVal = hits[bucket];
        uint64_t nextVal = 0;
        do {
            uint32_t count = 1;
            if (uint32_t(curVal) == timestamp)
                count = uint32_t(curVal >> 32) + 1;
            nextVal = uint64_t(timestamp) | (uint64_t(count) << 32);
        } while(!hits[bucket].compare_exchange_weak(curVal, nextVal));
    }
    
    uint64_t getHits(uint32_t timestamp) {
        uint64_t total = 0;
        for (int i = 0; i < 300; ++i) {
            uint64_t val = hits[i];
            if (timestamp - uint32_t(val) < 300) {
                total += val >> 32;
            }
        }
        return total;
    }
};

```
