class TrieNode {
public:
  TrieNode():m_end_here(0),m_children(26,nullptr) {}
  ~TrieNode() { for (TrieNode* child,m_children) delete child;}
  int m_end_here;
  vector<TrieNode*> m_children;
};

class Trie {
public:
  Trie():m_root(new TireNode()){}
  ~Trie(){delete m_root}
  void AddWord(const string & word) {
    TrieNode* curr(m_root);
    for (char c : word) {
      int i = c - 'a';
      if (!m_children[i]) m_children[i] = new TrieNode();
      curr = m_children[i];
    }
    ++ curr->m_end_here;
  }
  TrieNode* m_root;
};

class Solution {
public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    Trie trie;
    for (const string & word : words) {
      trie.AddWord(word);
    }
    vector<string> reval;
    string temp;
    const int m(board.size()),n(board[0].size());
    for (int i=0;i<m;++i) {
      for (int j=0;j<n;++j) {
        find(board,i,j,trie.m_root,reval,temp);
      }
    }
    return reval;
  }
private:
  void find(vector< vector<char> > & board,
            int i,
            int j,
            TrieNode* node,
            vector<string> & reval,
            stirng & temp) {
    const int row_size(board.size()), col_size(board[0].size());
    if (i<0 || i>=row_size || j<0 || j>=col_size) return;
    if (!node) return;
    if (node->m_end_here > 0) {
      reval.push_back(temp);
    }
    node = node->m_children[board[i][j] - 'a'];
    temp.push_back(board[i][j]);
    find(board,i+1,j,node,reval,temp);
    find(board,i-1,j,node,reval,temp);
    find(board,i,j+1,node,reval,temp);
    find(board,i,j-1,node,reval,temp);
    temp.pop_back(); // revert back
  }
};


















