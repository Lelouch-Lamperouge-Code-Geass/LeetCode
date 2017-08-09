Design a data structure that supports the following two operations:

```
void addWord(word)
bool search(word)
```

search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

For example:

```
addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
```
Note:
You may assume that all words are consist of lowercase letters a-z.

# Solution

```cpp
class TrieNode {
  friend class WordDictionary;
public:
  TrieNode():m_end_here(0), m_children(26,nullptr) {}
  ~TrieNode() { for (TrieNode* child : m_children) delete child;}
private:
  int m_end_here;
  vector<TrieNode*> m_children;
};

class WordDictionary {
public:
  WordDictionary():m_root(new TrieNode()) {}
  ~WordDictionary() {delete m_root;}
  // Adds a word into the data structure.
  void addWord(string word) {
    TrieNode * curr(m_root);
    for (char c : word) {
      int i = c - 'a';
      if (!curr->m_children[i]) curr->m_children[i] = new TrieNode();
      curr = curr->m_children[i];
    }
    ++ curr->m_end_here;
  }
  // Returns if the word is in the data structure. A word could
  // contain the dot character '.' to represent any one letter.
  bool search(const string & word) const {
    return search(word,0,m_root);
  }
private:
  bool search(const string & word,int pos,TrieNode* node) const {
    if (pos == word.size()) return node && node->m_end_here>0;
    if (word[pos] == '.') {
      for(TrieNode* child : node->m_children) {
        if (child && search(word,pos+1,child)) return true;
      }
      return false;
    } else {
      node = node->m_children[ word[pos]-'a'];
      return node && search(word,pos+1,node);
    }
  }

  TrieNode* m_root;
};
```
