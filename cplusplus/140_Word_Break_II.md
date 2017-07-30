Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary does not contain duplicate words.

Return all such possible sentences.

For example, given

```
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].
```

# Solution

##### Solution one

```cpp
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        std::unordered_set<std::string> word_set(wordDict.begin(), wordDict.end());
        std::unordered_map<std::string, std::unordered_set<std::string>> sentence_mapper;
        const std::unordered_set<std::string> &reval_set = getSentences(s, word_set, sentence_mapper);
        return std::vector<std::string>(reval_set.begin(), reval_set.end());
    }
private:
    std::unordered_set<std::string> getSentences(const std::string &s, 
                                       std::unordered_set<std::string> &word_set,
                                       std::unordered_map<std::string, std::unordered_set<std::string>> &sentence_mapper) {
        if (sentence_mapper.count(s) > 0) {
            return sentence_mapper[s];
        } else {
            std::unordered_set<std::string> reval;
            if (word_set.count(s) > 0) {
                reval.insert(s);
            }
            
            for (std::size_t cut = 1; cut < s.size(); ++ cut) {
                std::string left(s.substr(0, cut)), right(s.substr(cut));
                if (word_set.count(right) > 0) {
                    const std::unordered_set<std::string> &left_parts = getSentences(left, word_set, sentence_mapper);
                    for (const std::string &left : left_parts) {
                        reval.insert(left + ' ' + right);
                    }
                }
            }
            
            sentence_mapper[s] = reval;
            return reval;
        }
    }
};
```

##### Think about why this have  Time Limit Exceeded
```cpp
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        std::unordered_set<std::string> word_set(wordDict.begin(), wordDict.end());
        std::unordered_map<std::string, std::unordered_set<std::string>> sentence_mapper;
        const std::unordered_set<std::string> &reval_set = getSentences(s, word_set, sentence_mapper);
        return std::vector<std::string>(reval_set.begin(), reval_set.end());
    }
private:
    std::unordered_set<std::string> getSentences(const std::string &s, 
                                       std::unordered_set<std::string> &word_set,
                                       std::unordered_map<std::string, std::unordered_set<std::string>> &sentence_mapper) {
        if (sentence_mapper.count(s) > 0) {
            return sentence_mapper[s];
        } else {
            std::unordered_set<std::string> reval;
            if (word_set.count(s) > 0) {
                reval.insert(s);
            }
            
            for (std::size_t cut = 1; cut < s.size(); ++ cut) {
                std::string left(s.substr(0, cut)), right(s.substr(cut));
                const std::unordered_set<std::string> &left_parts = getSentences(left, word_set, sentence_mapper), 
                &right_parts = getSentences(right, word_set, sentence_mapper);
                
                if (!left_parts.empty() && !right_parts.empty()) {
                    for (const std::string &left : left_parts) {
                        for (const std::string &right : right_parts) {
                            reval.insert(left + ' ' + right);
                        }
                    }
                }
            }
            
            sentence_mapper[s] = reval;
            return reval;
        }
    }
};
```

##### Think about why below will have duplicates

```cpp
vector<string> wordBreakWithDp(unordered_map<string,vector<string>> & res,
                               const std::string & s,
                               unordered_set<string>& wordDict) {
  if (res.count(s)!=0) return res[s];
  const std::size_t s_size(s.size());
  vector<string> cur_res;
  if(wordDict.count(s)!=0) cur_res.push_back(s);
  for (std::size_t i=1;i<s_size;++i) {
    const vector<string> & left =  wordBreakWithDp(res,s.substr(0,i),wordDict);
    const vector<string> & right =  wordBreakWithDp(res,s.substr(i),wordDict);
    if (!left.empty() && !right.empty()) {
      for (const std::string & l : left) {
        for (const std::string & r : right) {
          cur_res.push_back(l+' '+r);
        }
      }
    }
  }
  res[s] = cur_res;// it could be empty
  return cur_res;
}
```
