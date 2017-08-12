Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:  

Only one letter can be changed at a time.  
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.  
For example,  

Given:

```
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
```

As one shortest transformation is ```"hit" -> "hot" -> "dot" -> "dog" -> "cog"```, return its length 5.

# Solution

Well, this problem has a nice BFS structure.

Let's see the example in the problem statement.

start = "hit"

end = "cog"

dict = ["hot", "dot", "dog", "lot", "log"]

Since only one letter can be changed at a time, if we start from "hit", we can only change to those words which have only one different letter from it, like "hot". Putting in graph-theoretic terms, we can say that "hot" is a neighbor of "hit".

The idea is simpy to begin from start, then visit its neighbors, then the non-visited neighbors of its neighbors... Well, this is just the typical BFS structure.

To simplify the problem, we insert end into dict. Once we meet end during the BFS, we know we have found the answer. We maintain a variable dist for the current distance of the transformation and update it by dist++ after we finish a round of BFS search (note that it should fit the definition of the distance in the problem statement). Also, to avoid visiting a word for more than once, we erase it from dict once it is visited.

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        std::unordered_set<std::string> word_set(wordList.begin(), wordList.end());
        if ( word_set.count(endWord) == 0
            || beginWord == endWord) return 0;
        
        std::unordered_set<std::string> left, right;
        left.insert(beginWord);
        right.insert(endWord);
        
        int edge(0);
        while (!left.empty() && !right.empty()) {
            if (meet(left, right)) {
                return edge + 1;
            } else {
                if (left.size() < right.size()) {
                    eraseWords(left, word_set);
                    left = getNext(left, word_set);
                } else {
                    eraseWords(right, word_set);
                    right = getNext(right, word_set);
                }
                ++ edge;
            }
        }
        
        // left and right never meet
        return 0;
    }
    
private:
    // erase words from word_set 
    void eraseWords(const std::unordered_set<std::string> &words,
                    std::unordered_set<std::string> &word_set) {
        for (const string & word : words) {
            word_set.erase(word);
        }
    }
    
    // check whether left and right have mutual word
    bool meet(std::unordered_set<std::string> &left, 
              std::unordered_set<std::string> &right) {
        bool reval(false);
        for (const string &temp : left) {
            if (right.count(temp) > 0) {
                reval = true;
                break;
            }
        }
        return reval;
    }
    
    // Works like BFS, return all possible words current level can reach based on the dictionary.
    // You can say this function return all the neighbors of the input nodes.
    std::unordered_set<std::string> getNext(const std::unordered_set<std::string> &words, 
                                            const std::unordered_set<std::string> &word_set) {
        std::unordered_set<std::string> reval;
        
        for (string word : words) {
            for (char & c : word) {
                const  char reserve = c;
                for (char t = 'a'; t <= 'z'; ++t) {
                    c = t;
                    
                    if (word_set.count(word) > 0) {
                        reval.insert(word);
                    }
                }
                c = reserve; // revert back
            }
        }
        return reval;
    }
};
```
