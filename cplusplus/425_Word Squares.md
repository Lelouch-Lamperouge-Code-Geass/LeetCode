Given a set of words (without duplicates), find all [word squares](https://en.wikipedia.org/wiki/Word_square) you can build from them.

A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 ≤ k < max(numRows, numColumns).

For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.

```
b a l l
a r e a
l e a d
l a d y
```

Note:

1. There are at least 1 and at most 1000 words.
2. All words will have the exact same length.
3. Word length is at least 1 and at most 5.
4. Each word contains only lowercase English alphabet a-z.

Example 1:

```
Input:
["area","lead","wall","lady","ball"]

Output:
[
  [ "wall",
    "area",
    "lead",
    "lady"
  ],
  [ "ball",
    "area",
    "lead",
    "lady"
  ]
]

Explanation:
The output consists of two word squares. The order of output does not matter 
(just the order of words in each word square matters).
```

Example 2:

```
Input:
["abat","baba","atan","atal"]

Output:
[
  [ "baba",
    "abat",
    "baba",
    "atan"
  ],
  [ "baba",
    "abat",
    "baba",
    "atal"
  ]
]

Explanation:
The output consists of two word squares. The order of output does not matter 
(just the order of words in each word square matters).
```

# Solution

### Solution one, use Trie

Example: ["area","lead","wall","lady","ball"]

We know that the sequence contains 4 words because the length of each word is 4.  
Every word can be the first word of the sequence, let's take "wall" for example.  
Which word could be the second word? Must be a word start with "a" (therefore "area"), because it has to match the second letter of word "wall".  
Which word could be the third word? Must be a word start with "le" (therefore "lead"), because it has to match the third letter of word "wall" and the third letter of word "area".  
What about the last word? Must be a word start with "lad" (therefore "lady"). For the same reason above.  

The picture below shows how the prefix are matched while building the sequence.

![alt](https://discuss.leetcode.com/assets/uploads/files/1476809120456-wordsquare.png)


```cpp
class Solution {
private:
    struct TrieNode;
    typedef TrieNode* TrieNodePtr;
    struct TrieNode {
        TrieNode(char c) : m_char(c), m_children(26, nullptr), m_word_count(0) {} 
        ~TrieNode() {
            for (TrieNodePtr child : m_children) {
                delete child;
            }
        }
        char m_char;
        vector<TrieNodePtr> m_children;
        unordered_set<std::string> m_start_with;
        std::size_t m_word_count;
    };
    
    struct Trie {
        Trie(const vector<string> &words) {
            m_root = new TrieNode(' ');
            for (const std::string &word : words) {
                TrieNodePtr curr = m_root;
                for (char c : word) {
                    if (!curr->m_children[c - 'a']) {
                        curr->m_children[c - 'a'] = new TrieNode('c');
                    }
                    curr->m_start_with.insert(word);
                    curr = curr->m_children[c - 'a'];
                }
                ++ curr->m_word_count;
            }
        }
        vector<string> getPrefixes(const std::string &str) const {
            TrieNodePtr curr = m_root;
            for (char c : str) {
                if (!curr->m_children[c - 'a']) {
                    return  vector<string>();
                } else {
                    curr = curr->m_children[c - 'a'];
                }
                
            }
            return vector<string>(curr->m_start_with.begin(), curr->m_start_with.end());
        }
        TrieNodePtr m_root;
    };
    
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        vector<vector<string>> reval;
        if (words.empty()) return reval;
        Trie trie(words);
        const std::size_t len(words[0].size());
        for (const std::string &word : words) {
            vector<string> square(1, word);
            dfs(reval, square, trie, len);
        }
        return reval;
    }
private:
    void dfs(vector<vector<string>> &reval,
            vector<string> &square,
            const Trie &trie,
            const std::size_t len) {
        if (square.size() == len) {
            reval.emplace_back(square);
        } else {
            const std::size_t idx(square.size());
            std::ostringstream oss("");
            for (const std::string &str : square) {
                oss << str[idx];
            }
            
            const vector<string> &prefixes = trie.getPrefixes(oss.str());
            for (const std::string &prefix : prefixes) {
                square.emplace_back(prefix);
                dfs(reval, square, trie, len);
                square.pop_back();
            }
        }
    }
};
```

