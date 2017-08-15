Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

```
[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
```

Note: All inputs will be in lower-case.

# Solution


```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> reval;
        std::unordered_map<std::string, std::size_t> mapper;
        for (const string &str : strs) {
            std::string temp(str);
            std::sort(temp.begin(), temp.end());
            if (mapper.count(temp) == 0) {
                reval.emplace_back(vector<string>());
                mapper.insert(std::make_pair(temp, reval.size() - 1));
            }
            
            reval[mapper[temp]].emplace_back(str);
        }
        
        return reval;
    }
};
```
