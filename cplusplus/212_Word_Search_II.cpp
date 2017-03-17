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
