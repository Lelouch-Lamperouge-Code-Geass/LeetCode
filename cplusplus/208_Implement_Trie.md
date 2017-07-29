Implement a trie with insert, search, and startsWith methods.
  
# Solution

```cpp
class TrieNode {
  friend class Trie;
public:
  // Initialize your data structure here.
  TrieNode() :m_end_here(0),m_children(26,nullptr){
  }
  ~TrieNode() {
    for (TrieNode* child : m_children) {
      delete child;
    }
  }
private:
  int m_end_here; //how many words end here
  vector<TrieNode*> m_children;
};

class Trie {
public:
  Trie() {
    root = new TrieNode();
  }

  ~Trie () {
    delete root;
  }
  // Inserts a word into the trie.
  void insert(string word) {
    TrieNode *curr(root);
    for (const char c : word) {
      int i = c - 'a';
      if (!curr->m_children[i]) curr->m_children[i] = new TrieNode();
      curr = curr->m_children[i];
    }
    ++ curr->m_end_here;
  }
  // Returns if the word is in the trie.
  bool search(string word) {
    TrieNode* curr = find(word);
    return curr && curr->m_end_here > 0 ;
  }

  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(string prefix) {
    TrieNode *curr = find(prefix);
    return curr != nullptr;
  }

private:
  // search and return the last node if word exists in this trie.
  // otherwise return null.
  TrieNode* find(const string & word) {
    TrieNode *curr(root);
    for (const char c: word) {
      int i = c - 'a';
      if (!curr->m_children[i]) return nullptr;
      curr = curr->m_children[i];
    }
    return curr;
  }
  TrieNode* root;
};
```
