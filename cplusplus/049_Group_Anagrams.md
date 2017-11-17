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

The simple solution is to use a std::unordered_map<string, vector<string>>, and for each string in strs, we get its hash code by sort it. And then add the push the string into the the related vector (HashMap[HashCode(str)]). Eventually, we add each vector in the HashMap to our result.

While we can do better than this.

We still get the hashcode of each string by sorting it. While if the hashcode is not present in the hashmap, we add an empty vector in our final result first (this means that this group of anagrams has not be found yet). And in our hashmap, we store the <hashcode, index_of_the_anagram_group>. And in the following step, for string which belongs to the same anagram group, we just add it into our final result based on the relationship recorded in our hashmap. Lovely!

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
