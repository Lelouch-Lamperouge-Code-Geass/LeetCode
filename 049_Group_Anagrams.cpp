class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> reval;
    unordered_map<string,int> mapper;
    for (const std::string & str : strs) {
      std::string copy(str);
      std::sort(copy.begin(),copy.end());
      if (mapper.find(copy)==mapper.end()) {
        reval.push_back(vector<string>());
        mapper[copy] = reval.size()-1;
      }
      reval[ mapper[copy] ].push_back(str);
    }
    return reval;
  }
};
