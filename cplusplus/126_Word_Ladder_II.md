Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

```
Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
Return

 [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
```

Note:  
* Return an empty list if there is no such transformation sequence.
* All words have the same length.
* All words contain only lowercase alphabetic characters.
* You may assume no duplicates in the word list.
* You may assume beginWord and endWord are non-empty and are not the same.

# Knowledge

### Bidirectional search

* https://en.wikipedia.org/wiki/Bidirectional_search

__Bidirectional search__ is a graph search algorithm that finds a shortest path from an initial vertex to a goal vertex in a directed graph. It runs two simultaneous searches: one forward from the initial state, and one backward from the goal, stopping when the two meet in the middle. The reason for this approach is that in many cases it is faster.

In normal graph search using BFS/DFS we begin our search in one direction usually from source vertex toward the goal vertex, but what if we start search form both direction simultaneously. Bidirectional search is a graph search algorithm which find smallest path form source to goal vertex. It runs two simultaneous search 

1. Forward search form source/initial vertex toward goal vertex
2. Backward search form goal/target vertex toward source vertex

Bidirectional search replaces single search graph(which is likely to grow exponentially) with two smaller sub graphs – one starting from initial vertex and other starting from goal vertex. The search terminates when two graphs intersect.


# Solution

We are required to return the SHORTEST transformation sequences in the end. How to build the transformation sequence then? It turns out if we can store the next transformation words for each word, then we can build the paths based on that.
Therefore, a HashMap stores <word, vector<next-transformation>> pairs will be a good choice.

How to generate the transformation mapper? Using BFS! Moreover, we can use Bi-directional BFS. Bi-direction BFS means simultaneously run two BFS's from both source and target vertices, terminating once a vertex common to both runs is discovered. We can return the transformation mapper once the common vertices are found, because we are find __SHORTEST__ sequences.

```cpp
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> begin_words = {beginWord}, end_words= {endWord};
        unordered_set<string> word_set(wordList.begin(), wordList.end());
        if (word_set.count(endWord) == 0) {
            // Ok, one unit test requires that if endWord is not in wordList,
            // return empty container
            return vector<vector<string>>();
        }
        unordered_map<string, vector<string>> nexts;
        vector<vector<string>> ladders;
        vector<string> ladder;
        if (BidirectionalBFS(begin_words, end_words, word_set, nexts, true)) {
            generateLadders(beginWord, endWord, nexts, ladders, ladder);
        }
        
        return ladders;
    }
    
private:
     void generateLadders(const string &begin_word,
                          const string &end_word,
                          unordered_map<string, vector<string>> &nexts,
                          vector<vector<string>> & ladders,
                          vector<string> &ladder) {
         ladder.emplace_back(begin_word);
         if (begin_word == end_word) {
             ladders.emplace_back(ladder);
         } else {
             for (const string &next : nexts[begin_word]) {
                 generateLadders(next, end_word, nexts, ladders, ladder);
             }
         }
         ladder.pop_back(); // revert back
     }
    // Perform bidirectional BFS, return true if ladder exist.
    // Since we are required to find all SHORTEST transformation 
    // sequence(s) from beginWord to endWord. We can safely stop further checking once
    // begin_words and end_words have overlap.
    bool BidirectionalBFS(unordered_set<string> &begin_words, 
                          unordered_set<string> &end_words,
                          unordered_set<string> &word_set,
                          unordered_map<string, vector<string>> &nexts,
                          bool path_not_reversed
                       ) {
        if (begin_words.empty() || end_words.empty()) {
            // No solution
            return false;
        } else {
            if (begin_words.size() > end_words.size()) {
                return BidirectionalBFS(end_words, begin_words, word_set, nexts, !path_not_reversed);
            } else {
                // make sure visited word not get visited again
                for (const string & word : begin_words)
                    word_set.erase(word);
                for (const string & word : end_words)
                    word_set.erase(word);
                if (getNextWords(begin_words, end_words, word_set, nexts, path_not_reversed)) {
                    return true;
                } else {
                    return BidirectionalBFS(end_words, begin_words, word_set, nexts, !path_not_reversed);
                }
            }
        }
    }
    // get next reachable words based on word dictionary
    bool getNextWords(unordered_set<string> & begin_words,
                   unordered_set<string> & end_words,
                   unordered_set<string> & word_set,
                   unordered_map<string, vector<string>> &nexts,
                   bool path_not_reversed) {
        bool reval(false);
        unordered_set<string> next_words;
        for (const string &word : begin_words) {
            string vary(word);
            for (char & c : vary) {
                const char origin_char = c;
                for (char i = 'a'; i <= 'z'; ++i) {
                    if (i != origin_char) {
                        c = i;
                        // Now we changed one char of original word
                        if (end_words.count(vary) > 0) {
                            // Meet
                            reval = true;
                            path_not_reversed? nexts[word].emplace_back(vary) 
                                : nexts[vary].emplace_back(word);
                        } else if (word_set.count(vary) > 0) {
                            next_words.insert(vary);
                            path_not_reversed ? nexts[word].emplace_back(vary) 
                                : nexts[vary].emplace_back(word);
                        }
                    }
                }
                c = origin_char; // revert back
            }
        }
        begin_words =  next_words;
        return reval;
    }
};
```

# Full code with unit tests

```cpp
// get next reachable words based on word dictionary
bool getNextWords(unordered_set<string> & begin_words,
                  unordered_set<string> & end_words,
                  unordered_set<string> & word_set,
                  unordered_map<string, vector<string>> &nexts,
                  bool path_not_reversed) {
  bool reval(false);
  unordered_set<string> next_words;
  for (const string &word : begin_words) {
    string vary(word);
    for (char & c : vary) {
      const char origin_char = c;
      for (char i = 'a'; i <= 'z'; ++i) {
        if (i != origin_char) {
          c = i;
          // Now we changed one char of original word
          if (end_words.count(vary) > 0) {
            // Meet
            reval = true;
            path_not_reversed? nexts[word].emplace_back(vary)
              : nexts[vary].emplace_back(word);
          } else if (word_set.count(vary) > 0) {
            next_words.insert(vary);
            path_not_reversed ? nexts[word].emplace_back(vary)
              : nexts[vary].emplace_back(word);
          }
        }
      }
      c = origin_char; // revert back
    }
  }
  begin_words =  next_words;
  return reval;
}

void UnitTest_getNextWords() {
  unordered_set<string> begin_words = {"hit"}, end_words = {"cog"};
  unordered_set<string> word_net = {"hot","dot","dog","lot","log","cog"};
  unordered_map<string, vector<string>> nexts;
  assert(getNextWords(begin_words, end_words, word_net, nexts, true) == false);
  assert(begin_words.size() == 1);
  assert(*begin_words.begin() == "hot");
  word_net.erase("hot");
  assert(getNextWords(begin_words, end_words, word_net, nexts, true) == false);
  assert(begin_words.size() == 2);
  assert(begin_words.count("dot") == 1);
  assert(begin_words.count("lot") == 1);
  word_net.erase("dot");
  word_net.erase("lot");
  assert(getNextWords(begin_words, end_words, word_net, nexts, true) == false);
  assert(begin_words.size() == 2);
  assert(begin_words.count("dog") == 1);
  assert(begin_words.count("log") == 1);
  word_net.erase("dog");
  word_net.erase("log");
  assert(getNextWords(begin_words, end_words, word_net, nexts, true) == true);
  assert(begin_words.size() == 0);
}

bool BidirectionalBFS(unordered_set<string> &begin_words,
                      unordered_set<string> &end_words,
                      unordered_set<string> &word_set,
                      unordered_map<string, vector<string>> &nexts,
                      bool path_not_reversed
                      ) {
  if (begin_words.empty() || end_words.empty()) {
    // No solution
    return false;
  } else {
    if (begin_words.size() > end_words.size()) {
      return BidirectionalBFS(end_words, begin_words, word_set, nexts, !path_not_reversed);
    } else {
      // make sure visited word not get visited again
      for (const string & word : begin_words)
        word_set.erase(word);
      for (const string & word : end_words)
        word_set.erase(word);
      if (getNextWords(begin_words, end_words, word_set, nexts, path_not_reversed)) {
        return true;
      } else {
        return BidirectionalBFS(end_words, begin_words, word_set, nexts, !path_not_reversed);
      }
    }
  }
}

void UnitTest_BidirectionalBFS() {
  unordered_set<string> begin_words = {"hit"}, end_words = {"cog"};
  unordered_set<string> word_net = {"hot","dot","dog","lot","log","cog"};
  unordered_map<string, vector<string>> nexts;
  assert(BidirectionalBFS(begin_words, end_words, word_net, nexts, true) == true);
  assert(nexts.size() == 6);
  
  assert(nexts["hit"].size() == 1 && nexts["hit"][0] == "hot");
  assert(nexts["hot"].size() == 2 && nexts["hot"][0] == "dot" && nexts["hot"][1] == "lot");
  assert(nexts["dot"].size() == 1 && nexts["dot"][0] == "dog");
  assert(nexts["lot"].size() == 1 && nexts["lot"][0] == "log");
  assert(nexts["dog"].size() == 1 && nexts["dog"][0] == "cog");
  assert(nexts["log"].size() == 1 && nexts["log"][0] == "cog");
}

void generateLadders(const string &begin_word,
                     const string &end_word,
                     unordered_map<string, vector<string>> &nexts,
                     vector<vector<string>> & ladders,
                     vector<string> &ladder) {
  ladder.emplace_back(begin_word);
  if (begin_word == end_word) {
    ladders.emplace_back(ladder);
  } else {
    for (const string &next : nexts[begin_word]) {
      generateLadders(next, end_word, nexts, ladders, ladder);
    }
  }
  ladder.pop_back(); // revert back
}


void UnitTest_generateLadders() {
  unordered_set<string> begin_words = {"hit"}, end_words = {"cog"};
  unordered_set<string> word_net = {"hot","dot","dog","lot","log","cog"};
  string beginWord("hit"), endWord("cog");
  unordered_map<string, vector<string>> nexts;
  assert(BidirectionalBFS(begin_words, end_words, word_net, nexts, true) == true);
  assert(nexts.size() == 6);
  
  vector<vector<string>> ladders;
  vector<string> ladder;
  generateLadders(beginWord, endWord, nexts, ladders, ladder);
  assert(ladders.size() == 2);
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
  unordered_set<string> begin_words = {beginWord}, end_words= {endWord};
  unordered_set<string> word_set(wordList.begin(), wordList.end());
  unordered_map<string, vector<string>> nexts;
  vector<vector<string>> ladders;
  vector<string> ladder;
  if (BidirectionalBFS(begin_words, end_words, word_set, nexts, true)) {
    generateLadders(beginWord, endWord, nexts, ladders, ladder);
  }

  return ladders;
}

void UnitTest_findLadders() {
  string beginWord("hit"), endWord("cog");
  vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
  
  vector<vector<string>> ladders = findLadders(beginWord, endWord, wordList);
  assert(ladders.size() == 2);
}

void UnitTest() {
  UnitTest_getNextWords();
  UnitTest_BidirectionalBFS();
  UnitTest_generateLadders();
}

int main() {
  UnitTest();
  return 0;
}
```
