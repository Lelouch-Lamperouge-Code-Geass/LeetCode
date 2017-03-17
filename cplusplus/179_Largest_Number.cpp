class Solution {
public:
  string largestNumber(vector<int>& nums) {
    vector<string> vec;
    for (int num : nums) {
      vec.push_back( std::to_string(num) );
    }
    std::sort(vec.begin(),vec.end(), Compare());
    string reval = std::accumulate(vec.begin(),vec.end(),string(""));
    return reval.size() > 1 && reval[0]=='0' ? "0" : reval;
  }
private:
  class Compare {
  public:
    bool operator() (const string & left, const string & right) {
      return left + right > right + left;
    }
  };
};
