Given many words, words[i] has weight i.

Design a class WordFilter that supports one function, WordFilter.f(String prefix, String suffix). It will return the word with given prefix and suffix with maximum weight. If no word exists, return -1.

##### Examples:
Input:
WordFilter(["apple"])
WordFilter.f("a", "e") // returns 0
WordFilter.f("b", "") // returns -1

##### Note:

* words has length in range [1, 15000].
* For each test case, up to words.length queries WordFilter.f may be made.
* words[i] has length in range [1, 10].
* prefix, suffix have lengths in range [0, 10].
* words[i] and prefix, suffix queries consist of lowercase letters only.

# Solution


### Solution one

We knows that each word has maximum length 10, so we can use a naive solution : use the combinations of every prefixes and every suffixes as a HashKey, and for words have the same HashKey, only stores the highest index(weight).


__Time complexity and space complexity are both O(NumberOfWords * LengthOfWord ^ 2).__

The downside is that it cost a lot of memory, and initialization is time-consuming. The good thing is that the fetch function will only cost O(1).

```cpp
class WordFilter {
private:
    // Stores hash of prefix and suffix to weight.
    unordered_map<string, int> m_hashmap;
public:
    WordFilter(vector<string> words) {
        for (int i = 0, n = words.size(); i < n; ++i) {
            for (int prefix_len = 0; prefix_len <= words[i].size(); ++prefix_len){
                for (int suffix_len = 0; suffix_len <= words[i].size(); ++suffix_len) {
                    string hash = words[i].substr(0, prefix_len) + '#' + words[i].substr(words[i].size() - suffix_len);
                    m_hashmap[hash] = i; // Always store the bigger weight
                }
            }
        }
    }
    
    int f(string prefix, string suffix) {
        if ( m_hashmap.count(prefix + '#' + suffix) > 0 ) {
            return m_hashmap[prefix + '#' + suffix];
        } else {
            return -1;
        }
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter obj = new WordFilter(words);
 * int param_1 = obj.f(prefix,suffix);
 */
 ``
 
### Solution two
 
We can change a little bit based on solution one. If we stores every prefixes and suffixes separately, then we can reduce time/space complexity to O(NumberOfWords * LengthOfWord). But right now the fetch function will cost O(NumberOfWords) because we need to fetch a list of words matching prefix, and a list of words matching suffix, and then choose the overlap word with maximum weight.


### Solution three

```cpp
struct TrieNode {
    vector<int> indexes_of_words; // index of words
    vector<TrieNode *> children;
    TrieNode() {
        children = vector<TrieNode *>(26, nullptr);
    }
    // Thanks to @huahualeetcode for adding this in case of memory leak
    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (children[i]) {
                delete children[i];
            }
        }
    }
    
    void add(const string &word, size_t begin, int index) {
        indexes_of_words.push_back(index);
        if (begin < word.length()) {
            if (!children[word[begin] - 'a']) {
                children[word[begin] - 'a'] = new TrieNode();
            }
            children[word[begin] - 'a']->add(word, begin + 1, index);
        }
    }
    
    vector<int> find(const string &prefix, size_t begin) {
        if (begin == prefix.length()) {
            return indexes_of_words;
        } else {
            if (!children[prefix[begin] - 'a']) {
                return {};
            } else {
                return children[prefix[begin] - 'a']->find(prefix, begin + 1);
            }
        }
    }
};

class WordFilter {
public:
    WordFilter(vector<string> words) {
        forwardTrie = new TrieNode();
        backwardTrie = new TrieNode();
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            forwardTrie->add(word, 0, i);
            reverse(word.begin(), word.end());
            backwardTrie->add(word, 0, i);
        }
    }
    
    int f(string prefix, string suffix) {
        // Return an iterator of vector of words.
        auto forwardMatch = forwardTrie->find(prefix, 0);
        reverse(suffix.begin(), suffix.end());
        auto backwardMatch = backwardTrie->find(suffix, 0);
        
        // Return the first match
        auto fIter = forwardMatch.rbegin(), bIter = backwardMatch.rbegin();
        while (fIter != forwardMatch.rend() && bIter != backwardMatch.rend()) {
            if (*fIter == *bIter) {
                return *fIter;
            } else if (*fIter > *bIter) {
                fIter ++;
            } else {
                bIter ++;
            }
        }
        return -1;
    }
    
private:
    TrieNode *forwardTrie, *backwardTrie;
};
```
