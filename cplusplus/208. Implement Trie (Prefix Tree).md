Implement a trie with insert, search, and startsWith methods.

##### Note:

You may assume that all inputs are consist of lowercase letters a-z.
  
# Solution

The problem is simple.

But you need to be careful about memory when using C/C++. If you are using raw pointers, you need to define the destructor to free memory.

You need to define a destructor whenever your constructor (or anything else in your class) acquires resources that would not ordinarily be released by the default constructor. This might include things like:

* Memory allocated with new
* A lock
* An open file descriptor


Usually, we don't need to store the char in Trie, but here I did it anyway. In practical, I use this information for debugging.

Time complexity : O(n) for inserting and searching strings ; [n = length of the string]

Space complexity : O(number_of_nodes), or you can say if there are N words and max word length is M, then space complexity is O(MN).


```cpp
class Trie {
private:
    struct TrieNode;
    typedef TrieNode* TrieNodePtr;
    struct TrieNode {
      TrieNode(char c) : m_char(c), m_word_count(0), m_children(26, nullptr){
          
      }
      /* Need to free dynamically allocated memory.  */
      ~TrieNode() {
          for (TrieNodePtr &child : m_children) {
              delete child;
          }
      }
      char m_char;
      int m_word_count;  
      std::vector<TrieNodePtr> m_children;    
    };
    TrieNodePtr m_root;
    /* search and return the last node if word exists in this trie,
       otherwise return null.*/
    TrieNodePtr findNode(const string&str) {
        TrieNodePtr curr = m_root;
        for (char c : str) {
            int i = c - 'a';
            if (!curr->m_children[i]) {
                return nullptr;
            }
            curr = curr->m_children[i];
        }
        return curr;
    }
public:
    /** Initialize your data structure here. */
    Trie() {
        m_root = new TrieNode(' ');
    }
    
    /* Need to free dynamically allocated memory. */
    ~Trie() {
        delete m_root;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNodePtr curr = m_root;
        for (char c : word) {
            int i = c - 'a';
            if (!curr->m_children[i]) {
                curr->m_children[i] = new TrieNode(c);
            }
            curr = curr->m_children[i];
        }
        ++ curr->m_word_count;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNodePtr curr = findNode(word);
        return curr && curr->m_word_count > 0;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return findNode(prefix) != nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */
```

# Knowledge 

### Trie

In computer science, a __trie__, also called digital tree and sometimes radix tree or prefix tree (as they can be searched by prefixes), is a kind of search tree—an ordered tree data structure that is used to store a dynamic set or associative array where the keys are usually strings. Unlike a binary search tree, no node in the tree stores the key associated with that node; instead, its position in the tree defines the key with which it is associated. All the descendants of a node have a common prefix of the string associated with that node, and the root is associated with the empty string. Values are not necessarily associated with every node. Rather, values tend only to be associated with leaves, and with some inner nodes that correspond to keys of interest. For the space-optimized presentation of prefix tree, check __compact prefix tree__.
