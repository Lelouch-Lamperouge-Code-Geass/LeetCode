/* Solution 1 */
class Solution {
public:
  typedef std::pair<int,int> Item;// <number,count>

  vector<int> topKFrequent(vector<int>& nums, int k) {
    std::unordered_map<int,int> counter; //[number, count]
    for (int num:nums) {
      ++ counter[num];
    }

    std::priority_queue<Item,std::vector<Item>,PqCompare> pq;
    for (const Item & item : counter) {
      pq.push(item);
      if (pq.size()>k) pq.pop();
    }

    vector<int> reval;
    while (!pq.empty()) {
      reval.push_back(pq.top().first);
      pq.pop();
    }
    return reval;
  }
private:
  class PqCompare {
  public:
    bool operator() (const Item & left, const Item & right) {
      return left.second > right .second;
    }
  };
};

/* Solution 2 */
class Solution {
public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    const int nums_size(nums.size());
    // Calculate the frequency of each number
    std::unordered_map<int,int> counter;
    for (int num : nums) {
      ++ counter[num];
    }
    // Push the number into different bucket based on its frequence
    vector< vector<int> > frequency(nums_size+1,vector<int>());
    for (const std::pair<int,int> & item : counter) {
      frequency[item.second].push_back(item.first);
    }

    vector<int> reval;
    for (int fix = nums_size;fix>=0;--fix) {
      if(frequency[fix].empty()) continue;
      for (int num : frequency[fix]) {
        if (reval.size()==k) return reval;
        reval.push_back(num);
      }
    }
    return reval;
  }
};
