Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,

```
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
```

Return ["eat","oath"].

# Solution
Intuitively, start from every cell and try to build a word in the dictionary. Backtracking (dfs) is the powerful way to exhaust every possible ways. Apparently, we need to do pruning when current character is not in any word.

* How do we instantly know the current character is invalid? HashMap?  
* How do we instantly know what's the next valid character? LinkedList?  
* But the next character can be chosen from a list of characters. "Mutil-LinkedList"?  
  
Combing them, Trie is the natural choice. Notice that:

* TrieNode is all we need. search and startsWith are useless.  
* No need to store character at TrieNode. c.next[i] != null is enough.  
* Never use c1 + c2 + c3. Use StringBuilder.  
* No need to use O(n^2) extra space visited[m][n].  
* No need to use StringBuilder. Storing word itself at leaf node is enough.  
* No need to use HashSet to de-duplicate. Use "one time search" trie.  
  
The time complexity to make a trie structure is O(words_count * word_length).
The time complexity to lookup a word in a trie structure is O(word_length).
  
# Solution one 
  
```cpp
class Solution {
public:
  class TrieNode {
  public:
    TrieNode() : m_count(0),m_children(26,nullptr) {}
    ~TrieNode() {for (TrieNode* child : m_children) delete child;}
    int m_count;
    vector<TrieNode*> m_children;
  };

  class Trie {
  public:
    Trie() : m_root(new TrieNode()) { }
    ~Trie() {delete m_root;}
    void AddWord(const std::string & word) {
      TrieNode* curr(m_root);
      for (const char c : word) {
        if (!curr->m_children[c-'a']) {
          curr->m_children[c-'a'] = new TrieNode();
        }
        curr = curr->m_children[c-'a'];
      }
      ++ curr->m_count;
    }
    TrieNode* m_root;
  };

  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    if(board.empty() || words.empty()) return vector<string>();
    Trie trie;
    for (const std::string & word : words) {
      trie.AddWord(word);
    }

    vector<string> res;
    const std::size_t row_size(board.size()),col_size(board[0].size());
    std::string temp("");
    for (std::size_t i=0;i<row_size;++i) {
      for (std::size_t j=0;j<col_size;++j) {
        FindWithDfs(res,temp,board,trie.m_root,i,j);
      }
    }
    return res;
  }
private:
  void FindWithDfs(vector<string> & res,
                   string & temp,
                   vector<vector<char>>& board,
                   const TrieNode * node_ptr,
                   const std::size_t row,
                   const std::size_t col) {
    const std::size_t row_size(board.size()),col_size(board[0].size());
    if (row>=row_size || col>=col_size || board[row][col] == '#' || !node_ptr)
      return; // notice we are using size_t which is non-negative
    const char cur_char = board[row][col];
    if (!node_ptr->m_children[cur_char-'a'])
      return;
    board[row][col] = '#';
    temp.push_back(cur_char);
    if (node_ptr->m_children[cur_char-'a']->m_count>0) { // find a word
      res.push_back(temp);
      // We can use a HashSet to de-duplicate, but here we reset m_count
      // in trie. It is a small trick
      node_ptr->m_children[cur_char-'a']->m_count = 0;
    }
    node_ptr = node_ptr->m_children[cur_char-'a'];
    FindWithDfs(res,temp,board,node_ptr,row-1,col);
    FindWithDfs(res,temp,board,node_ptr,row+1,col);
    FindWithDfs(res,temp,board,node_ptr,row,col-1);
    FindWithDfs(res,temp,board,node_ptr,row,col+1);

    //revert back
    temp.pop_back();
    board[row][col] = cur_char;
  }
};
```

# Solution two : same methology as solution one

```cpp
struct TrieNode;
typedef std::shared_ptr<TrieNode> TrieNodePtr;

struct TrieNode {
    TrieNode(char c) : m_char(c), m_count(0), m_children(26, nullptr) {
        
    }
    char m_char;
    int m_count;
    std::vector<TrieNodePtr> m_children;
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        const TrieNodePtr trie_root = buildTrieBasedOnWords(words);
        std::unordered_set<string> words_set;
        std::string temp("");
        for (std::size_t row = 0, row_size = board.size(); row < row_size; ++ row) {
            for (std::size_t col = 0, col_size = board[row].size(); col < col_size; ++ col) {
                searchInTrie(words_set, board, row, col, trie_root, temp);
            }
        }
        return std::vector<std::string> (words_set.begin(), words_set.end());
    }
private:
    void addWordToTrie(const TrieNodePtr &root, const std::string &word) {
        TrieNodePtr node = root;
        
        for (char c : word) {
            if ( !node->m_children[c - 'a'] ) {
                node->m_children[c - 'a'] = std::make_shared<TrieNode>(c);
            }
            
            node = node->m_children[c - 'a'];
        }
        
        ++ node->m_count;
    }
    
    TrieNodePtr buildTrieBasedOnWords(const std::vector<std::string> &words) {
        TrieNodePtr root = std::make_shared<TrieNode>('#');
        
        for (const std::string &word : words) {
            addWordToTrie(root, word);
        }
        
        return root;
    }
    
    void searchInTrie( std::unordered_set<string> &words_set,
                     vector<vector<char>> &board,
                     std::size_t row,
                     std::size_t col,
                     const TrieNodePtr &node_ptr,
                     std::string &temp) {
        if (board.empty()) return;
        const std::size_t row_size(board.size()), col_size(board[0].size());
        
        if (!node_ptr || board[row][col] == '#') return;
        
        if (node_ptr->m_char == '#') { // Trie root node
            for (const TrieNodePtr &child : node_ptr->m_children) {
                searchInTrie(words_set, board, row, col, child, temp);
            }
        } else {
        
            if (node_ptr->m_char == board[row][col]) {
                const char cur_char = board[row][col];
                temp.push_back(cur_char);
                board[row][col] = '#';

                if ( node_ptr->m_count > 0) { // find a word
                    words_set.insert(temp);
                    -- node_ptr->m_count;
                }

                for (const TrieNodePtr &child : node_ptr->m_children) {
                    if (row + 1 < row_size) searchInTrie(words_set, board, row + 1, col, child, temp);
                    if (row > 0) searchInTrie(words_set, board, row - 1, col, child, temp);
                    if (col + 1 < col_size) searchInTrie(words_set, board, row, col + 1, child, temp);
                    if (col > 0) searchInTrie(words_set, board, row, col - 1, child, temp);
                }

                // revert back
                board[row][col] = cur_char;
                temp.pop_back();
            }
        }
    }
};
```
