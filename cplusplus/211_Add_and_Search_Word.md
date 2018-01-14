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

We begin with root TrieNode, if we find a corresponding child node that can match current char, move to that node.

__Note that in below implementaion, when we reach a node, the pos's value is actually the 

```
                      root
                    /   \    \
                    t   a     b
                    |   |     |
                    e   n     y
                    |   |  \  |
                    a   s  y  e
```


### Solution one : need to clear memory when use raw pointer

```cpp
class WordDictionary {
private:
    struct TrieNode;
    typedef TrieNode* TrieNodePtr;
    struct TrieNode {
        TrieNode() : m_children(26, nullptr), m_word_count(0) {
            
        }
        ~TrieNode() {
            // We know that the child pointers have dynamic memory allocated.
            // Therefore we need clear those memory on heap.
            for (const TrieNodePtr & child : m_children) {
                delete child;
            }
        }
        vector<TrieNodePtr> m_children;
        int m_word_count;
    };
    TrieNodePtr m_root;
    
    bool searchWithDFS(TrieNodePtr curr, 
                       const string &word,
                       int next_pos) {
        if (next_pos == word.size()) return curr->m_word_count > 0;
      
        if (word[next_pos] != '.') {
            if (!curr->m_children[word[next_pos] - 'a']) {
                return false;
            } else {
                return searchWithDFS(curr->m_children[word[next_pos] - 'a'], word, next_pos + 1);
            }
        } else {
            for (TrieNodePtr child : curr->m_children) {
                if (child && searchWithDFS(child, word, next_pos + 1)) {
                    return true;
                }
            }
            return false;
        }
    }
public:
    /** Initialize your data structure here. */
    WordDictionary() : m_root(new TrieNode()){
        
    }
    
    ~WordDictionary() {
        delete m_root; // Free memory on heap.
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNodePtr curr = m_root;
        for (char c : word) {
            if (!curr->m_children[c - 'a']) {
                curr->m_children[c - 'a'] = new TrieNode();
            }
            curr = curr->m_children[c - 'a'];
        }
        ++ curr->m_word_count;
    }
    
    /** Returns if the word is in the data structure. 
    A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchWithDFS(m_root, word, 0);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */
```

### Solution two : Use shared_ptr
```cpp
class WordDictionary {
private:
    struct TrieNode;
    typedef std::shared_ptr<TrieNode> TrieNodePtr;
    struct TrieNode {
      TrieNode(char c) : m_char(c), m_word_count(0), m_children(26, nullptr) {
          
      }
      char m_char;
      std::size_t m_word_count;
      std::vector<TrieNodePtr> m_children;
    };
    
    TrieNodePtr m_root;
public:
    /** Initialize your data structure here. */
    WordDictionary() : m_root(std::make_shared<TrieNode>(' ')){
        
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNodePtr cur(m_root);
        for (char c : word) {
            std::size_t index = c - 'a';
            if (cur->m_children[index] == nullptr) {
                cur->m_children[index] = std::make_shared<TrieNode>(c);
            }
            cur = cur->m_children[index];
        }
        
        ++ cur->m_word_count;
    }
    
    /** Returns if the word is in the data structure. 
      A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchWithDFS(m_root, word, 0);
    }
private:
    bool searchWithDFS(const TrieNodePtr & node_ptr, const string &word, std::size_t pos) {
        if (pos == word.size()) return node_ptr && node_ptr->m_word_count > 0;
        
        if (word[pos] == '.') {
            for (const TrieNodePtr &child : node_ptr->m_children) {
                if (child && searchWithDFS(child, word, pos + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            std::size_t index = word[pos] - 'a';
            return node_ptr->m_children[index] 
                && searchWithDFS(node_ptr->m_children[index], word, pos + 1);
        }
    }
};
```

# Knowledge

### Trie

In computer science, a __trie__, also called __prefix tree__ (as they can be searched by prefixes), is a kind of search tree—an ordered tree data structure that is used to store a dynamic set or associative array where the keys are usually strings. Unlike a binary search tree, no node in the tree stores the key associated with that node; instead, its position in the tree defines the key with which it is associated. All the descendants of a node have a common prefix of the string associated with that node, and the root is associated with the empty string. Values are not necessarily associated with every node. Rather, values tend only to be associated with leaves, and with some inner nodes that correspond to keys of interest. 

The name trie comes from its use for re__trie__val. It is pronounced like "try" by some, like "tree" (the pronunciation of "trie" in "retrieval") by others. 

### What does a destructor do in C++ and how it is related to delete keyword?

Calling ‘delete’ is always paired with a previous ‘new’ statement, whereas the destructor is (meant to be) called automatically at the end of scope.

In C++, any variable/object not declared using the ‘new’ keyword (and also not declared as static) is allocated in the stack and is destroyed automatically at the end of its scope. This is when an object’s destructor is automatically called, and its purpose is to properly clean up any resources that object had ownership of (e.g., private variables declared using ‘new’).

On the other hand, when you declare an object using ‘new’, you are reserving space in dynamic memory (the heap), and just you get the pointer to the beginning of that allocated space. Because all you have is a raw pointer (assuming it’s not a smart pointer), no destructor is called at the end of scope. Anything created using ‘new’ requires a matching ‘delete’ statement somewhere else in the code, otherwise you have what we call a ‘memory leak’, i.e. memory that your program reserved but never deallocated when it was supposed to.
