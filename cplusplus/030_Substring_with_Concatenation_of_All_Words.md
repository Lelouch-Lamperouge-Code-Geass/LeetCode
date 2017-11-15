You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

```
For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]
```

You should return the indices: [0,9].
(order does not matter).
 
 
# Solution

The brute-force solution works like this : for each index in string s, we check the window end(or begin if you like) with that index, and see whether that window match the requirements. This means that for each index, we need use another pointer 'window_start' to traverse all the words within this window and see whether there is a 'conflict word' (word not in the words list). The checking process takes O(window_size) time. And the total time complexity is O(window_size * s.size()).
 
First of all, you need to know that above brute-force solution have many unnecessary calculations. Every time we found this is a 'conflict word' in this window, we should skip the 'conflict word'. For example, if we find there is a 'conflict word' when we are checking the window end with index i. There is no point to check the index after i whose window also have this conflict word. 
 
How can we do better ?  
 
We can make the window sliding from the begining of s untill its end. If everytime we find a 'conflict word', we can just shift the window_start right after the conflict word. For every window which meet the requirements, we just add the window_start into our final result.

```
For "conflict word", there are two scenarios:

1. The conflict word doesn't in our words list at all, and in this case we need to shift the begin position of the window right after the conflict word.

2. The conflict word is actually a word in our words list, but in this window we have more than we need. In this case, we need to shift the begin position of the window right after the first word matching our conflict word.
```

By closing look at these two cases, it turns out that all we need to do is to _shift the begin position right after the first word matching our conflict word_.

But wait a minute. By sliding from beging of the string s only, is definitely not enough. Because it only covers index begin with 

```0, word_size, word_size * 2, word_size * 3,......```

How about window begin with 1, 2, 3 ?
 
It turns out that one window sliding is not good enough, __we need word.size() times of window sliding__.
 
__Since for each window sliding, every char comes into and out of the window only once, the time complexity for one window sliding is O(s.size()). And because we need to perform word.sizs() times of window sliding, the total time complexity is O(s.size() * word.size()).__
 
```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> reval;
        if (words.empty()) return reval;
        const std::size_t word_size(words[0].size()), s_size(s.size());
        std::unordered_map<std::string, int> word_counter;
        for (const std::string &word : words) {
            ++ word_counter[word];
        }
        
        const int total_words(words.size());
        
        // We need to perform word_size times of window sliding in total!
        // Each window sliding, every char comes into and goes out of the window once.
        // Therefore, each window sliding cost O(length of s).
        for (std::size_t i = 0; i < word_size; ++i) {
            int words_to_found(total_words);
            std::unordered_map<std::string, int> window_word_counter = word_counter;
            
            std::size_t window_start(i), cur_pos(i);
            
            while (cur_pos + word_size <= s_size) {
                const std::string cur_word(s.substr(cur_pos, word_size));
                
                if (window_word_counter[cur_word] > 0) {
                    // Sweet! Found a word!
                    -- words_to_found;
                    -- window_word_counter[cur_word];
                } else {
/****************************************************************************************
// Attention! A conflict word appears!
// Note that all other words in this window are not conflict word because we process window
// immediately whenever we encounter one conflict word.

// Two cases here:
// 1. The conflict word doesn't in our words list at all, and in this case we need to shift the begin position 
//    of the window right after the conflict word.
// 2. The conflict word is actually a word in our words list, but in this window we have more than we need.
//    In this case, we need to shift the begin position of the window right after the first word 
//    matching our conflict word.
// By closing look at these two cases, it turns out that all we need to do is to
// shift the begin position right after the first word matching our conflict word! 
******************************************************************************************/

                    
                    if (word_counter.count(cur_word)) { // Attention! We check against original word counter here.
                        // Case 2, let's put cur_word into window first
                        -- words_to_found;
                        -- window_word_counter[cur_word];
                    }
                    
                    // Begin process current window until after processing the first word that matching cur_word.
                    while (window_start <= cur_pos) {
                        const std::string drop_word(s.substr(window_start, word_size));
                        if (word_counter.count(drop_word) > 0) {
                            ++ words_to_found;
                            ++ window_word_counter[drop_word];
                        }
                        window_start += word_size;
                        if (drop_word == cur_word) {
                            break;
                        }
                    }

                }
                
                if (words_to_found == 0) {
                    reval.emplace_back(window_start);
                }
                
                cur_pos += word_size;
            }
        }
        
        return reval;
    }
};
```

A fater solution after optimization.
 
```cpp 
class Solution {
 public:
  vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> res;
    if (s.empty() || words.empty()) return res;
    const int s_size(s.size()), word_len(words[0].size()),
        word_num(words.size()), word_len_combi(word_len * word_num);
    if (s_size < word_len_combi) return res;
    unordered_map<string, int> mapper;
    for (const string& word : words) {
      mapper.find(word) == mapper.end() ? mapper[word] = 1 : ++mapper[word];
    }

    int start(0), cur(0), word_num_remain(word_num);
    for (int i = 0; i < word_len; ++i) {
      start = cur = i;
      while (start <= s_size - word_len * word_num_remain) {
        const string cur_word(s.substr(cur, word_len));
        if (mapper.find(cur_word) == mapper.end()) {
          // Not found, reset
          for (word_num_remain = word_num; start != cur; start += word_len) {
            ++mapper[s.substr(start, word_len)];
          }
          start += word_len;  // skip the current invalid word;
        } else if (mapper[cur_word] == 0) {
          // Already found, reset
          for (; cur_word != s.substr(start, word_len); start += word_len) {
            ++mapper[s.substr(start, word_len)];
            ++word_num_remain;
          }
          start += word_len;  // skip the previous found one;
        } else {
          --mapper[cur_word];
          if (--word_num_remain == 0) {
            res.push_back(start);
            ++mapper[s.substr(start, word_len)];
            start += word_len;
            ++word_num_remain;
          }
        }
        cur += word_len;
      }

      for (; start < cur; start += word_len)
        ++mapper[s.substr(start, word_len)];  // reset the map count
    }
    return res;
  }
};
```
