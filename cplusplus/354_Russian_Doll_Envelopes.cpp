// Sort the array. Ascend on width and descend on height if width are same.
// Find the longest increasing subsequence based on height.
// Since the width is increasing, we only need to consider height.
// IMPORTANT! [3, 4] cannot contains [3, 3], so we need to put [3, 4] before [3, 3]
// when sorting otherwise it will be counted as an increasing number if the order is [3, 3], [3, 4]

class Solution {
private:
  struct PairCompare {
    bool operator()(const pair<int,int> & left, const pair<int,int> & right) {
                return left.first < right.first
                                    || left.first == right.first && left.second > right.second;
    }
  };
public:
  int maxEnvelopes(vector<pair<int, int>>& envelopes) {
    std::sort(envelopes.begin(), envelopes.end(), PairCompare());
    std::vector<int> increasing_height;
    for (const pair<int,int> & envelope : envelopes) {
      std::vector<int>::iterator iter = std::lower_bound(increasing_height.begin(),
                                                         increasing_height.end(),
                                                         envelope.second);
      if (iter == increasing_height.end() ) {
        increasing_height.push_back(envelope.second);
      } else {
        *iter = envelope.second;
      }
    }
    return increasing_height.size();
  }
};
